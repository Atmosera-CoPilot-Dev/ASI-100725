# Healthcare Mini-Normalizer Challenge (Focused Build)

## Overview
Implement a focused C# (.NET 8) console app that streams a single CSV of mixed VISIT and LAB records, validates each line, normalizes into canonical objects, applies minimal terminology mapping, masks patient names, tracks core counts, and prints a concise summary. Single pass, in-memory, no database.

## Core Goals
- Streaming parse (File.ReadLines) – no full file load
- Canonical models: Patient, Visit, LabResult, Rejection, MetricsContainer
- Layered validation with rejection reasons
- Terminology mapping (reason + test) with unmapped counter
- Privacy: simple deterministic masking only (first char + ***)
- Core metrics only (lines, patients, visits, labs, rejections, unmapped)
- Robust to malformed lines (reject & continue)

## Input Format
`RecordType,MRN,PatientName,DOB,Date,Code,Value`
- VISIT: Date = VisitDate, Code = ReasonCode, Value ignored
- LAB: Date = CollectedDate, Code = TestCode, Value = numeric lab value

## Canonical Models
- Patient: MRN, Name, MaskedName, DOB
- Visit: VisitId, MRN, VisitDate, ReasonCodeOriginal, ReasonCodeMapped
- LabResult: ResultId, MRN, TestCodeOriginal, TestCodeMapped, Value, CollectedDate
- Rejection: LineNumber, ReasonCode
- MetricsContainer: totalLines, totalPatients, visitCount, labCount, rejectedCount, unmappedCodesCount

## Validation Rules (Order)
1. Structural column count → Structural
2. Missing MRN → MissingMRN
3. MRN regex invalid → InvalidMRNFormat
4. Name length >128 → NameTooLong
5. Date parse failure (DOB or event) → InvalidDate
6. Future DOB or event date → FutureDate
7. RecordType not VISIT/LAB → UnknownRecordType
8. LAB numeric parse failure → InvalidLabValue
9. (Optional) Empty Code warning → WarnEmptyCode (not a rejection)

## Terminology Mapping
Interface recommended:
```
public interface ITerminologyMapper {
  string MapReason(string original, Action unmappedCallback);
  string MapTest(string original, Action unmappedCallback);
}
```
Defaults:
- Reasons: R001→Annual, R002→FollowUp else "Unknown" (+ unmapped)
- Tests: GLU→LOINC-GLU, HCT→LOINC-HCT else unmapped (mapped empty string)

## Privacy (Masking Only)
Rule: first alphanumeric char + ***; empty/null → *.

## Metrics Summary Line
`Lines=X Patients=Y Visits=V Labs=L Rejected=R Unmapped=U`

## Processing Flow
1. Stream lines
2. Increment totalLines
3. Parse → validate
4. On rejection: record & continue
5. Upsert patient (by trimmed MRN) with masking
6. Map codes (unmapped callback increments counter)
7. Create Visit or LabResult; increment counts
8. Print summary + patient list + optional rejection grouping

## Configuration (Minimal)
```
public class NormalizerConfig {
  public string DataFilePath { get; init; }
  public int SoftLineWarningThreshold { get; init; }
  public int HardLineStopThreshold { get; init; }
}
```

## Acceptance Criteria
Must:
- Summary line prints all six metrics
- ≥3 rejection reasons reachable
- Unmapped reason + test increment counter
- MaskedName differs from original
- Duplicate MRN counted once
- Single pass processing
- ≥5 passing NUnit tests

Should:
- Mapper via interface
- Thresholds honored (soft warning logged, hard stop enforced or remaining lines rejected Structural)

May:
- Warning counter if implementing WarnEmptyCode
- Simple interactive query loop

## Test Suggestions
1. Missing MRN → MissingMRN
2. Unknown reason code → Unknown + unmapped increment
3. Unknown test code → unmapped increment
4. Masking edge cases (normal, single char, empty)
5. Future date → FutureDate
6. Invalid lab value → InvalidLabValue (or duplicate MRN consolidation)

## Extension Ideas (After Core)
- JSON metrics export
- Rejections CSV
- Progress output every N lines
- Additional mapping sets via configuration

## How to Run
1. Place `data.csv` in project or specify path in config
2. Build & run: observe summary output
3. Run tests: `dotnet test`

## Reflection Prompts
- Which validation caught the most issues?
- What would you reintroduce first for richer analytics (hashing, timing, memory)?
- Next step to add a second file type?

---
Keep scope strict: normalization, mapping, masking, metrics counts.
