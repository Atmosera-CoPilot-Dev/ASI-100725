# .NET / C#

Provide an expert-level breakdown of the built‑in Roslyn analyzer ecosystem for C# (CA*, IDE*, security-oriented rules), AnalysisLevel (latest vs preview), nullable reference types as a semantic safety net, .editorconfig severity mapping (error/warn/silent/none), selective /warnaserror usage for security categories, solution‑wide vs project analyzer configuration, and performance trade‑offs in large multi-target solutions.

Produce a comparative evaluation of supplemental .NET static/security analyzers that emit SARIF (SecurityCodeScan, DevSkim, CodeQL C# queries, Semgrep .NET rules, SonarC#, Snyk Code, commercial SAST). For each, outline strongest detection domains (taint/dataflow, cryptography misuse, insecure deserialization, injection vectors, SSRF), typical false‑positive patterns, licensing/operational cost, and recommended layering order.

Detail a hardened procedure to configure Roslyn analyzers for high-fidelity SARIF output: global.json SDK pinning, Directory.Build.props (EnableNETAnalyzers, AnalysisLevel, AnalysisMode, TreatWarningsAsErrors scoped via <WarningsAsErrors>), granular .editorconfig severity tuning, reproducible path normalization (ContinuousIntegrationBuild=true), msbuild invocation with /p:ErrorLog=artifacts/roslyn.sarif;logfileformat=Sarif, generation of an HTML/markdown summary, and diffing SARIF against a stored baseline.

Design a polyglot GitHub Actions workflow that merges C# (Roslyn + SecurityCodeScan) with ESLint and Pylint SARIF: matrix (os, dotnet-version), analyzer caching, conditional incremental scans on pull_request (changed files only via git diff + targeted dotnet build), scheduled full scan (weekly) refreshing baselines, concurrency cancellation for superseded builds, severity and count thresholds gating merges, and artifact retention strategy.

Explain end‑to‑end SARIF ingestion into GitHub Code Scanning: fingerprint construction (ruleId + location + partialFingerprints), handling multi‑OS path normalization, baseline vs new vs reopened alert semantics, root causes of dropped results (non-canonical URIs, missing uriBaseId, truncated large SARIF), verification via gh api code-scanning alerts list, and techniques to validate deduplication during refactors.

Provide an advanced technical profile of SecurityCodeScan: rule taxonomy (injection, XSS in Razor, insecure crypto, path traversal, insecure deserialization), Roslyn semantic model usage, dataflow (source/sink/sanitizer) customization potential, overlap/gap analysis versus CodeQL + DevSkim, strategies to tune precision (custom sinks, narrowing patterns), and recommended suppression governance.

List precise steps to integrate SecurityCodeScan into a multi-target (net6.0, net8.0) solution: PackageReference pinning (Central Package Management), analyzer inclusion in Directory.Build.props, conditional TreatWarningsAsErrors for only security rule IDs, validating analyzer execution (binary log + /bl), and ensuring IDE + CI parity (same .editorconfig + config file).

Provide a SecurityCodeScan.config example that: elevates critical injection/crypto rules, demotes noisy or contextually mitigated rules, excludes generated /obj /bin and designer/EF migrations, customizes additional sources/sinks, tags rules with rationale comments, and documents a justification template for auditors.

Show a GitHub Actions job snippet that restores caches (NuGet + intermediate obj), executes dotnet build with analyzers (/p:ErrorLog=...sarif), invokes SecurityCodeScan (if separate), uploads SARIF (actions/upload-sarif), summarizes counts per severity in the job summary, and fails fast on infrastructure errors while deferring policy gating to a later evaluation step.

Provide a workflow_dispatch-enabled security scan workflow with typed inputs (failOnHigh:boolean, fullScan:boolean, refreshBaseline:boolean), minimum permissions (contents: read, security-events: write), OIDC-based artifact signing or provenance attestation, and safeguards preventing secret echoing (set -o pipefail; no verbose token logs).

Describe a policy enforcement script (jq / minimal C# console) that: normalizes SARIF severities across tools, correlates with a stored baseline (tracking hashes + ruleId), supports waiver metadata (expiresOn, approvedBy), fails the build on new High/Critical or expired waivers, and emits an actionable summary table + remediation guidance URL mapping.
