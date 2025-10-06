# Bank Transaction Monitoring System - 90-Minute Focused Exercise

## Visual Studio Solution & Project Structure (Start Here)

To reduce ambiguity, create a minimal, focused solution with these projects:

Required (baseline for the exercise):
1. Banking.Core (Class Library - .NET 8)
   - Domain models: BankAccount hierarchy, Transaction, SuspicionRecord, AuditEntry
   - Services: TransactionProcessor, SuspiciousActivityDetector, DailySummaryService
   - Interfaces: IAccountRepository, ITransactionProcessor, ISuspiciousActivityDetector, ISuspiciousRule, IAuditLog
   - Settings/config class (e.g., MonitoringSettings)
   - In-memory repositories (no external storage)
2. Banking.Tests (NUnit Test Project - .NET 8)
   - Test suites: Accounts, Transactions (including concurrency), Suspicious rules, Reporting
   - Deterministic data; no randomness; all UTC

Optional (only if time remains):
3. Banking.Console (Console App) – manual demo driver (create sample accounts, run a few transactions, print summary)
4. Banking.Rules (Class Library) – if you want to physically separate rule implementations from core abstractions
5. Banking.Infrastructure (Class Library) – placeholder for persistence/logging extensions (stretch)

Folder layout suggestion inside Banking.Core:
- Accounts/ (BankAccount.cs, CheckingAccount.cs, SavingsAccount.cs, BusinessAccount.cs)
- Transactions/ (Transaction.cs, TransactionProcessor.cs)
- Suspicious/ (ISuspiciousRule.cs, LargeAmountRule.cs, RapidFireRule.cs, SuspiciousActivityDetector.cs)
- Reporting/ (DailySummaryService.cs, DailySummary.cs)
- Audit/ (IAuditLog.cs, InMemoryAuditLog.cs, AuditEntry.cs)
- Settings/ (MonitoringSettings.cs)
- Repositories/ (IAccountRepository.cs, InMemoryAccountRepository.cs)
- Common/ (enums, status types, guard helpers)

Assembly guidance:
- Keep public surface minimal; internal where possible (InternalsVisibleTo for tests if needed).
- All timestamps in UTC (DateTime.UtcNow).
- No static mutable state except safe atomic counters (e.g., Interlocked for account numbers).

Add these references:
- Banking.Tests -> reference Banking.Core
- (Optional) Console -> reference Banking.Core

NuGet packages (minimum):
- NUnit
- NUnit3TestAdapter
- Microsoft.NET.Test.Sdk

---

## Ordered Copilot Prompt Script (Sequential Use)

1. "Create MonitoringSettings class with properties: LargeAmountThreshold, RapidFireCount, RapidFireWindow, BusinessOverdraftLimit, SavingsMinimumBalance."
2. "Scaffold abstract BankAccount with Id (Guid), AccountNumber (long), AccountType enum, protected ApplyDelta method enforcing constraints; make it thread-safe with a private lock."
3. "Implement CheckingAccount, SavingsAccount (min balance), BusinessAccount (overdraft limit) inheriting BankAccount."
4. "Create IAccountRepository with async methods AddAsync, GetAsync, GetAllAsync; implement InMemoryAccountRepository using ConcurrentDictionary and atomic account number generator."
5. "Define Transaction model with immutable properties: Id, UtcTimestamp, Type enum, Amount, SourceAccountId, TargetAccountId, Status enum, FailureReason."
6. "Create ITransactionProcessor interface with DepositAsync, WithdrawAsync, TransferAsync returning Transaction."
7. "Implement TransactionProcessor ensuring ordered locking by Guid for transfers, appending to a thread-safe ledger (ConcurrentQueue<Transaction>)."
8. "Add sum-of-balances invariant comment and expose IReadOnlyCollection<Transaction> via a snapshot method."
9. "Define ISuspiciousRule (Id, Description, Evaluate) and SuspicionRecord with Severity enum."
10. "Implement LargeAmountRule using MonitoringSettings.LargeAmountThreshold."
11. "Implement RapidFireRule using rolling window: N transactions within TimeSpan window per source account."
12. "Create ISuspiciousActivityDetector and implementation evaluating each completed transaction and storing open suspicion records thread-safely."
13. "Add IAuditLog and InMemoryAuditLog with append-only list and methods to query entries."
14. "Instrument TransactionProcessor to write audit entries for each processed transaction."
15. "Add method to mark suspicion reviewed: record analyst, resolution note, close timestamp."
16. "Create DailySummary model and DailySummaryService that aggregates totals, rejected count, suspicious count, net deltas per account type."
17. "Generate NUnit tests: SavingsAccount minimum balance enforcement, BusinessAccount overdraft boundary, rejection beyond overdraft."
18. "Generate NUnit test: LargeAmountRule triggers only above threshold; RapidFireRule triggers exactly at configured count in window."
19. "Generate concurrency test: parallel transfers among multiple accounts preserve global sum."
20. "Generate reporting test verifying DailySummary totals and per-account-type deltas."
21. "Add XML documentation comments to all public types and members."
22. "Add guard clauses for negative amounts throwing ArgumentOutOfRangeException before processing."
23. "Refactor shared validation into a private helper inside TransactionProcessor."
24. "Polish: ensure all timestamps use DateTime.UtcNow and no synchronous blocking on tasks."

(You can copy/promote prompts individually while progressing through the timeline.)

---

This exercise is tailored for an experienced C# engineer using GitHub Copilot to complete a robust core implementation in ~90 minutes. It contains critical aspects: correctness, thread safety, extensibility hooks, and basic security posture.

---
## Objective (Focused)
Deliver an in-memory, test-backed transaction monitoring core supporting:
- Multiple account types with business rules
- Thread-safe deposit / withdrawal / transfer operations
- Suspicious activity detection via pluggable rules
- Minimal reporting + audit trail

---
## Essential Scope
1. Accounts
   - Abstract BankAccount + Checking, Savings (min balance), Business (overdraft limit)
   - Thread-safe balance mutation
   - Unique account numbers (atomic counter or GUID)
2. Transactions
   - Transaction model (Id, UTC time, type, amount, source, target, status, reason)
   - Async TransactionProcessor with Deposit/Withdraw/TransferAsync
   - Lock ordering for transfers (order by account id)
   - Immutable ledger list/queue
3. Suspicious Activity
   - ISuspiciousRule abstraction
   - Rules: LargeAmountRule, RapidFireRule (N tx in window)
   - Detector producing SuspicionRecord; review action to resolve
4. Reporting & Audit
   - DailySummary: totals, rejected count, suspicious count, net deltas per account type
   - AuditLog entries for: account create/close, each transaction, suspicion review
5. Testing
   - NUnit tests covering: business rules, concurrency integrity, rule triggering, reporting totals
---
## Acceptance Criteria
- All public operations async (Task-returning)
- No data races under parallel transfer test (sum invariant maintained)
- Overdraft + min balance rules enforced deterministically
- Suspicious rules fire only under configured conditions
- All timestamps UTC
- Thresholds/rule configs centralized (Settings object)
- XML docs on public types/methods
- Tests complete <5s

---
## Suggested Timeline (Guide)
- 0–10 min: Models & interfaces skeleton
- 10–30 min: Account implementations + repository + balance safety
- 30–50 min: TransactionProcessor + basic tests
- 50–65 min: Suspicious rules + detector + tests
- 65–75 min: Reporting + audit log
- 75–90 min: Concurrency + final polishing tests

---
## Key Interfaces (Sketch You Can Prompt For)
- IAccountRepository
- ITransactionProcessor
- ISuspiciousActivityDetector
- ISuspiciousRule
- IAuditLog

---
## Sample Copilot Prompts
- "Scaffold abstract BankAccount with protected ApplyDelta enforcing non-negative unless overdraft allowed."
- "Implement thread-safe TransactionProcessor with ordered locking for transfers by Guid."
- "Create LargeAmountRule and RapidFireRule implementing ISuspiciousRule interface."
- "Generate NUnit test verifying 100 parallel transfers preserve global balance invariant."
- "Add audit logging wrapper for transaction methods returning decorated result." 

---
## Test Focus Areas
- SavingsAccount rejects withdrawal below minimum
- BusinessAccount allows overdraft up to limit then rejects
- Concurrency: parallel transfers (e.g., 20 tasks * 100 iterations)
- RapidFireRule: triggers when threshold met; not before
- LargeAmountRule: fires above threshold only
- Summary report aggregates numbers correctly

---
## Stretch (If Time Remains)
- CancellationToken support
- Structured logging (Serilog) adapter
- Additional rule (e.g., VelocityAmountRule: cumulative amount in window)
- Simple console status output

---
## Deliverables (Submit or Demo)
- Source with XML docs
- Settings/config class for rule thresholds
- All NUnit tests green
- Short README note describing design trade-offs

---
## Quality Checklist
- No blocking on async over sync (avoid .Result / .Wait())
- Deterministic locking order for multiple accounts
- No secret/PII leakage in audit or logs
- Rule evaluation isolated / easily pluggable
- Invariants documented in tests (sum of balances)

---
