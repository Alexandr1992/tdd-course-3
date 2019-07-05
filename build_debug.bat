cmake -Htdd_intro -Bbuild64_debug -G"Visual Studio 14 2015 Win64" || goto :eof
cmake --build build64_debug --target install --config Debug || echo build64_debug failed && goto :eof

:: to run tests
pushd build64_debug
ctest -VV -C Debug || echo Unit-tests failed && popd && goto :eof
popd