# Manufacturing Simulation Workshop

(Primary specification: see microchips.md. This README provides solution structure, build order, and prompts.)

---

## 0. Visual Studio Solution & Project Structure

Target framework: .NET 8

Projects:
1. Manufacturing.Core (Class Library)
   - Domain: MicroWidget, FailureEvent, InspectionResult
   - Configuration: SimulationConfig
   - Engines: AssemblyEngine, QualityControlEngine
   - Runtime: SimulationRunner
   - Logging: InMemoryEventLog
   - Queue: InMemoryWidgetQueue
   - Metrics: DailySummary, MetricsAggregator
   - Interfaces: IAssemblyEngine, IQualityControlEngine, IWidgetQueue, IEventLog
   - Utilities: SimpleRandom (seeded)
2. Manufacturing.Simulation (Console App)
   - Program.cs wiring + CLI (--days, --seed)
3. Manufacturing.Tests (NUnit)
   - Suites: AssemblyProduction, FailureImpact, QCLunch, Determinism, Backlog

Folder suggestions (Manufacturing.Core):
- Configuration/
- Domain/
- Engines/
- Interfaces/
- Logging/
- Metrics/
- Runtime/
- Queue/
- Util/

NuGet:
- NUnit
- NUnit3TestAdapter
- Microsoft.NET.Test.Sdk

Design notes:
- Single-threaded minute loop is acceptable.
- Seeded randomness via one SimpleRandom instance.
- Times represented as minute index (0..1439) per day; convert only for display if needed.
- Immutable records for events and summaries.

---

## 1. Scope Overview

You will implement a manufacturing + quality control simulation producing:
- Production, damaged, failures, downtime
- Inspection, defects, accepted
- Backlog (end-of-day + max)
- Utilization and system efficiency
- Deterministic results with seed
This is the canonical lab exercise.

---

## 2. Requirements Summary

Assembly (5 lines):
- Window: 07:00–13:00 (6h)
- Base hourly throughput: 80 (cap 100); optional uniform ±10 variance
- Damage probability: 0.005 per widget (damaged not queued)
- Failure: ≤1 per line per day, 10% chance; fixed 60-minute downtime
- Hourly batch deliveries + final day-end delivery

Quality Control (5 teams × 3 engineers):
- Window: 08:00–16:00 (8h)
- Lunch: 12:00–12:45 (no inspections)
- Capacity: engineers * 8 per hour → per-minute = floor(totalPerHour / 60)
- Defect probability: 0.025 per inspected widget

Queue:
- FIFO, unbounded
- Only receives hourly batches (and final daily batch)

Metrics per day:
- ProducedPerLine, DamagedPerLine
- FailuresPerLine, DowntimeMinutesPerLine
- TotalProduced, TotalGoodProduced
- TotalInspected, TotalAccepted, TotalDefects
- BacklogEndOfDay, MaxQueueLength
- LineUtilizationPerLine = (Scheduled - Downtime)/Scheduled (Scheduled=360)
- SystemEfficiency = TotalAccepted / TotalGoodProduced (guard zero)

---

## 3. Acceptance Criteria

- Deterministic with identical seed/config
- Lunch interval yields zero inspection throughput
- Backlog end-of-day > 0 under default config
- Utilization < 1 if any failure; = 1 if none
- Damage/defect counts valid (bounds respected)
- Core tests execute < 3s
- Public surface has XML documentation

---

## 4. Ordered Copilot Prompt Script

Paste sequentially:

1. "Create SimulationConfig with: Days, Seed, AssemblyLineCount=5, QCTeamCount=5, EngineersPerTeam=3, AssemblyStart=07:00, AssemblyHours=6, QCStart=08:00, QCHours=8, LunchStart=12:00, LunchMinutes=45, HourlyBaseThroughput=80, HourlyVariance=10, HourlyMax=100, DamageProbability=0.005, FailureChancePerLinePerDay=0.10, FailureDowntimeMinutes=60, QCPerEngineerPerHour=8, DefectProbability=0.025."
2. "Add TimeHelpers with IsAssemblyMinute(min), IsQCMinute(min), IsLunch(min)."
3. "Create records: MicroWidget(Guid Id, int LineId); InspectionResult(Guid WidgetId, bool IsDefective); FailureEvent(int LineId, int StartMinute, int DowntimeMinutes)."
4. "Create DailySummary with all required metric fields and per-line dictionaries."
5. "Add interfaces: IEventLog (Append, Snapshot), IWidgetQueue (EnqueueBatch, DequeueUpTo), IAssemblyEngine (Tick(minute)), IQualityControlEngine (Tick(minute)), IMetricsAggregator."
6. "Implement InMemoryEventLog (thread-safe)."
7. "Implement InMemoryWidgetQueue using Queue<MicroWidget> with locking."
8. "Implement SimpleRandom (seed) with NextInt(min,maxInclusive) and NextDouble()."
9. "Implement AssemblyEngine using SimulationConfig: track per-line state (producedThisHour, isFailed, downtimeLeft). Hour targets set at hour start (base ± variance clamped). Deliver batch on hour boundary or assembly end."
10. "Add failure logic at day start with probability; if failed set downtime countdown; skip production while downtime > 0."
11. "Implement QualityControlEngine: compute per-minute capacity; skip during lunch or outside QC window; dequeue up to capacity producing InspectionResult with defect probability."
12. "Implement MetricsAggregator methods to record production, damage, inspection, defects, failures, queue length (update MaxQueueLength)."
13. "Implement SimulationRunner looping days/minutes, calling assembly & QC engines, updating metrics, finalizing DailySummary at day end."
14. "Add console Program parsing --days and --seed, running SimulationRunner, printing DailySummary values."
15. "Add NUnit test: deterministic same-seed results equality."
16. "Add NUnit test: no inspection increments during lunch window."
17. "Add NUnit test: backlog > 0 at end of day."
18. "Add NUnit test: utilization < 1 when forced failures (set FailureChancePerLinePerDay=1)."
19. "Add XML docs to all public types."

Optional (after core):
20. "Add defect rate (%), and aggregate multi-day totals."

---

## 5. Suggested Timeline (Approx. 2 Hours)

- 0–15 min: Config + models + utilities
- 15–35 min: Assembly engine + queue
- 35–55 min: QC engine + metrics
- 55–70 min: Runner + console output
- 70–90 min: Tests
- 90–105 min: XML docs + polish
- Remaining: Optional enhancements

---

## 6. Test Focus

- DeterminismTest
- LunchPauseTest
- BacklogPositiveTest
- UtilizationFailureTest
- (Optional) ProbabilitySanityTest (multi-day run: counts > 0)

---

## 7. Quality Checklist

- Single seeded SimpleRandom
- No DateTime.Now (pure minute indices)
- Clear separation: engines produce data, runner orchestrates, console formats
- Constant-time queue ops
- XML docs present
- Warnings minimized
- Tests < 3s

---

## 8. Stretch Goals

- Per-minute wait tracking
- Gaussian sampling
- Scenario comparison runner
- CSV export
- Weekly summary aggregator

---

## 9. Quick Run

dotnet run --project Manufacturing.Simulation -- --days 1 --seed 123

---

## 10. Future Extension

Add richer distributions, queue latency, per-team metrics, multi-scenario analysis, export formats.

---