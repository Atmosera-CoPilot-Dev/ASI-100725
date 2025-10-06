# C++

Provide a sample PR templates that ties together MISRA C++ rules, cybersecurity controls, and static analysis output to strengthen code quality and security posture.

How can Copilot be systematically prompted to generate compliant code, reference specific rules, and align with PR and static analysis pipelines for security and safety standards?

Provide a comparative overview of key C++ static and security-focused analysis tools (Cppcheck, Clang-Tidy, Clang Static Analyzer, sanitizers, fuzzers, CodeQL, SARIF-producing linters, commercial options). When do I apply each for security vs safety vs quality vs compliance?

How do I implement Cppcheck in VS Code with: a tasks.json integration, MISRA C++ (2008/2023) addons (if available), inline and external suppressions, handling third-party headers efficiently?

How do I generate SARIF from both Cppcheck and Clang-Tidy, merge the results, and successfully upload them to GitHub Code Scanning (including severity mapping, baseline strategy, and troubleshooting missing alerts)?

Provide an advanced GitHub Actions workflow for a CMake-based C++ project that: runs matrix builds, caches dependencies and compile_commands.json, executes Cppcheck (security + MISRA profile), Clang-Tidy (selected security/cert checks), optional CodeQL, enforces fail-on-severity thresholds, and publishes SARIF + logs.

How do I enforce and reconcile MISRA C++ compliance alongside modern C++ features (move semantics, constexpr, templates) and compare/align MISRA vs CERT C++ vs AUTOSAR C++14 rules for a safety-critical codebase?

Show how to configure hardened and instrumented builds: integrating AddressSanitizer, UndefinedBehaviorSanitizer, ThreadSanitizer in debug, plus production hardening flags (-fstack-protector-strong, -D_FORTIFY_SOURCE=3, -fPIE -pie, relro/now, stack clash protection) while keeping analyzer compatibility.

What is the role of fuzz testing (libFuzzer, AFL++, honggfuzz) in complementing static analysis and sanitizers? Provide a minimal fuzz target, build flags, and CI integration pattern.

How do I implement secure third-party dependency management: SBOM generation (CycloneDX or Syft), hash pinning, license/security scanning, and integrate SBOM + static analysis artifacts into CI/CD reporting?

How can I gate merges by parsing SARIF to enforce policy (e.g., fail if new high-severity > 0)? Outline a lightweight script approach (jq or Node.js) and integration into GitHub Actions.

What are best practices to reduce false positives and maintain a sustainable suppression strategy (granular justifications, layered abstractions, RAII for resource safety, periodic suppression audits, differential scanning)?
