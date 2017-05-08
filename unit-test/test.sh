../bin/condense -f demo.data -p 2 -d " " > demo-reduced.res
RESULT_HASH=`shasum demo-reduced.res|awk '{print $1;}'` 
TEST_HASH=`shasum demo-reduced.data|awk '{print $1;}'` 
test "$RESULT_HASH" == "$TEST_HASH" && (echo Pass; exit 1)
