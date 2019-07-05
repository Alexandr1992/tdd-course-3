cmake -Htdd_intro -Bbuild64_release -G"Visual Studio 14 2015 Win64" || goto :eof
cmake --build build64_release --target install --config Release || echo build64_release failed && goto :eof

:: to run tests
pushd build64_release
ctest -C Release || echo Unit-tests failed && popd && goto :eof
popd