// Minimal embedded doctest header placeholder. For full functionality, fetch official doctest.h.
#ifndef DOCTEST_MINIMAL_HEADER
#define DOCTEST_MINIMAL_HEADER
#include <exception>
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <cstdlib>

namespace doctest {
    using TestFunc = void(*)();
    struct TestRegistry { std::vector<std::pair<std::string, TestFunc>> tests; static TestRegistry& inst(){ static TestRegistry r; return r;} };
    struct Register { Register(const char* name, TestFunc f){ TestRegistry::inst().tests.emplace_back(name,f);} };
    inline int run() { int fails=0; for(auto &p: TestRegistry::inst().tests){ try{ p.second(); } catch(const std::exception& e){ std::cout<<"[FAIL] "<<p.first<<" exception: "<<e.what()<<"\n"; ++fails; continue;} catch(...){ std::cout<<"[FAIL] "<<p.first<<" unknown exception\n"; ++fails; continue;} std::cout<<"[ OK ] "<<p.first<<"\n"; } std::cout<<TestRegistry::inst().tests.size()-fails<<" passed, "<<fails<<" failed\n"; return fails; }
}
#define DOCTEST_TEST_CASE(name) static void name(); static doctest::Register reg_##name(#name,&name); static void name()
#define DOCTEST_CHECK(x) do{ if(!(x)){ std::cout<<"[CHECK FAILED] "<<#x<<" at "<<__FILE__<<":"<<__LINE__<<"\n"; } }while(0)
#define DOCTEST_REQUIRE(x) do{ if(!(x)){ std::cout<<"[REQUIRE FAILED] "<<#x<<" at "<<__FILE__<<":"<<__LINE__<<"\n"; throw std::runtime_error("require failed"); } }while(0)
#ifdef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
int main(){ return doctest::run(); }
#endif
#endif
