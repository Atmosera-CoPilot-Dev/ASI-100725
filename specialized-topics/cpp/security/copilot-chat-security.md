## Python

Recommend static analysis tools for a Python project that focus on security vulnerabilities.

I need a quick review of Pylint with key features and limitations. Also include a sample Bandit command to scan a Python project.

How do I implement Bandit for a Python project built with VS Code?

How do I integrate Bandit into my CI/CD pipeline for automated security checks with GitHub Actions? 

## .NET 

What is the default static analysis tool for .NET projects?

Recommend other static analysis tools to generate SARIF reports that can be integrated into a CI/CD pipeline with GitHub Actions.

What are the steps to configure and generate a SARIF report using Roslyn Analyzers for a .NET project?

How can I use the SARIF format to integrate static analysis tools with my CI/CD pipeline?  Include an example of GitHub Actions workflow that integrates ESLint and Pylint to generate SARIF reports:

How do I integrate the SARIF report into GitHub's Security tab?

What is the SecurityCodeScan tool? How does it differ from other static analysis tools?

How do I implement SecurityCodeScan into my Visual Studio 2022 project?

Show a sample SecurityCodeScan.config that demonstrates basic customization. The example should  include enabling specific rules, disabling others, and configuring rule parameters.

How do I integrate SecurityCodeScan into my CI/CD pipeline for automated security checks with GitHub Actions? It needs to be able to use a custom  SecurityCodeScan.config file.

Show an example of the provided workflow that alse uses workflow dispatch to trigger the security scan.

Can I customize the GitHub Actions workflow to fail the build if any security issues are found?

## JavaScript/TypeScript

What are the recommended static analysis tools for JavaScript/TypeScript projects?

How do I implement ESLint for a JavaScript/TypeScript project built with VS Code?

What are the steps to configure and generate a SARIF report using ESLint for a JavaScript/TypeScript project?

How can I use the SARIF format to integrate static analysis tools with my CI/CD pipeline?  Include an example of GitHub Actions workflow that integrates ESLint and Pylint to generate SARIF reports:
How do I integrate the SARIF report into GitHub's Security tab?


## C++

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


