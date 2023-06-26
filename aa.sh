source ./activate
cd vm
make clean
make
cd build

#! /bin/bash
# 주의사항: vm 폴더 바로 하위에 본 파일을 저장하세요.
# 돌리고 싶은 테스트의 경우 주석 처리를 해제하세요.
# 본 파일을 executable로 만들고 싶다면 chmod u+x ${파일명}
# executable로 만든 후 사용 방법은 쉘에서 다음의 명령어를 입력하시면 됩니다: ./vm_test_automate.sh

# Project 1 - Threads
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run alarm-single < /dev/null 2> tests/threads/alarm-single.errors > tests/threads/alarm-single.output
# perl -I../.. ../../tests/threads/alarm-single.ck tests/threads/alarm-single tests/threads/alarm-single.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run alarm-multiple < /dev/null 2> tests/threads/alarm-multiple.errors > tests/threads/alarm-multiple.output
# perl -I../.. ../../tests/threads/alarm-multiple.ck tests/threads/alarm-multiple tests/threads/alarm-multiple.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run alarm-simultaneous < /dev/null 2> tests/threads/alarm-simultaneous.errors > tests/threads/alarm-simultaneous.output
# perl -I../.. ../../tests/threads/alarm-simultaneous.ck tests/threads/alarm-simultaneous tests/threads/alarm-simultaneous.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run alarm-priority < /dev/null 2> tests/threads/alarm-priority.errors > tests/threads/alarm-priority.output
# perl -I../.. ../../tests/threads/alarm-priority.ck tests/threads/alarm-priority tests/threads/alarm-priority.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run alarm-zero < /dev/null 2> tests/threads/alarm-zero.errors > tests/threads/alarm-zero.output
# perl -I../.. ../../tests/threads/alarm-zero.ck tests/threads/alarm-zero tests/threads/alarm-zero.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run alarm-negative < /dev/null 2> tests/threads/alarm-negative.errors > tests/threads/alarm-negative.output
# perl -I../.. ../../tests/threads/alarm-negative.ck tests/threads/alarm-negative tests/threads/alarm-negative.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-change < /dev/null 2> tests/threads/priority-change.errors > tests/threads/priority-change.output
# perl -I../.. ../../tests/threads/priority-change.ck tests/threads/priority-change tests/threads/priority-change.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-donate-one < /dev/null 2> tests/threads/priority-donate-one.errors > tests/threads/priority-donate-one.output
# perl -I../.. ../../tests/threads/priority-donate-one.ck tests/threads/priority-donate-one tests/threads/priority-donate-one.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-donate-multiple < /dev/null 2> tests/threads/priority-donate-multiple.errors > tests/threads/priority-donate-multiple.output
# perl -I../.. ../../tests/threads/priority-donate-multiple.ck tests/threads/priority-donate-multiple tests/threads/priority-donate-multiple.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-donate-multiple2 < /dev/null 2> tests/threads/priority-donate-multiple2.errors > tests/threads/priority-donate-multiple2.output
# perl -I../.. ../../tests/threads/priority-donate-multiple2.ck tests/threads/priority-donate-multiple2 tests/threads/priority-donate-multiple2.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-donate-nest < /dev/null 2> tests/threads/priority-donate-nest.errors > tests/threads/priority-donate-nest.output
# perl -I../.. ../../tests/threads/priority-donate-nest.ck tests/threads/priority-donate-nest tests/threads/priority-donate-nest.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-donate-sema < /dev/null 2> tests/threads/priority-donate-sema.errors > tests/threads/priority-donate-sema.output
# perl -I../.. ../../tests/threads/priority-donate-sema.ck tests/threads/priority-donate-sema tests/threads/priority-donate-sema.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-donate-lower < /dev/null 2> tests/threads/priority-donate-lower.errors > tests/threads/priority-donate-lower.output
# perl -I../.. ../../tests/threads/priority-donate-lower.ck tests/threads/priority-donate-lower tests/threads/priority-donate-lower.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-fifo < /dev/null 2> tests/threads/priority-fifo.errors > tests/threads/priority-fifo.output
# perl -I../.. ../../tests/threads/priority-fifo.ck tests/threads/priority-fifo tests/threads/priority-fifo.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-preempt < /dev/null 2> tests/threads/priority-preempt.errors > tests/threads/priority-preempt.output
# perl -I../.. ../../tests/threads/priority-preempt.ck tests/threads/priority-preempt tests/threads/priority-preempt.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-sema < /dev/null 2> tests/threads/priority-sema.errors > tests/threads/priority-sema.output
# perl -I../.. ../../tests/threads/priority-sema.ck tests/threads/priority-sema tests/threads/priority-sema.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-condvar < /dev/null 2> tests/threads/priority-condvar.errors > tests/threads/priority-condvar.output
# perl -I../.. ../../tests/threads/priority-condvar.ck tests/threads/priority-condvar tests/threads/priority-condvar.result
# pintos -v -k -T 60 -m 20   --fs-disk=10  --swap-disk=4 -- -q  -threads-tests -f run priority-donate-chain < /dev/null 2> tests/threads/priority-donate-chain.errors > tests/threads/priority-donate-chain.output
# perl -I../.. ../../tests/threads/priority-donate-chain.ck tests/threads/priority-donate-chain tests/threads/priority-donate-chain.result

# Proejct 2 - User Program - Passing Argument
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/args-none:args-none --swap-disk=4 -- -q   -f run args-none < /dev/null 2> tests/userprog/args-none.errors > tests/userprog/args-none.output
# perl -I../.. ../../tests/userprog/args-none.ck tests/userprog/args-none tests/userprog/args-none.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/args-single:args-single --swap-disk=4 -- -q   -f run 'args-single onearg' < /dev/null 2> tests/userprog/args-single.errors > tests/userprog/args-single.output
# perl -I../.. ../../tests/userprog/args-single.ck tests/userprog/args-single tests/userprog/args-single.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/args-multiple:args-multiple --swap-disk=4 -- -q   -f run 'args-multiple some arguments for you!' < /dev/null 2> tests/userprog/args-multiple.errors > tests/userprog/args-multiple.output
# perl -I../.. ../../tests/userprog/args-multiple.ck tests/userprog/args-multiple tests/userprog/args-multiple.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/args-many:args-many --swap-disk=4 -- -q   -f run 'args-many a b c d e f g h i j k l m n o p q r s t u v' < /dev/null 2> tests/userprog/args-many.errors > tests/userprog/args-many.output
# perl -I../.. ../../tests/userprog/args-many.ck tests/userprog/args-many tests/userprog/args-many.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/args-dbl-space:args-dbl-space --swap-disk=4 -- -q   -f run 'args-dbl-space two  spaces!' < /dev/null 2> tests/userprog/args-dbl-space.errors > tests/userprog/args-dbl-space.output
# perl -I../.. ../../tests/userprog/args-dbl-space.ck tests/userprog/args-dbl-space tests/userprog/args-dbl-space.result

# Proejct 2 - User Program - syscall tests that do not use fork
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/halt:halt --swap-disk=4 -- -q   -f run halt < /dev/null 2> tests/userprog/halt.errors > tests/userprog/halt.output
# perl -I../.. ../../tests/userprog/halt.ck tests/userprog/halt tests/userprog/halt.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/exit:exit --swap-disk=4 -- -q   -f run exit < /dev/null 2> tests/userprog/exit.errors > tests/userprog/exit.output
# perl -I../.. ../../tests/userprog/exit.ck tests/userprog/exit tests/userprog/exit.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/create-normal:create-normal --swap-disk=4 -- -q   -f run create-normal < /dev/null 2> tests/userprog/create-normal.errors > tests/userprog/create-normal.output
# perl -I../.. ../../tests/userprog/create-normal.ck tests/userprog/create-normal tests/userprog/create-normal.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/create-empty:create-empty --swap-disk=4 -- -q   -f run create-empty < /dev/null 2> tests/userprog/create-empty.errors > tests/userprog/create-empty.output
# perl -I../.. ../../tests/userprog/create-empty.ck tests/userprog/create-empty tests/userprog/create-empty.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/create-null:create-null --swap-disk=4 -- -q   -f run create-null < /dev/null 2> tests/userprog/create-null.errors > tests/userprog/create-null.output
# perl -I../.. ../../tests/userprog/create-null.ck tests/userprog/create-null tests/userprog/create-null.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/create-bad-ptr:create-bad-ptr --swap-disk=4 -- -q   -f run create-bad-ptr < /dev/null 2> tests/userprog/create-bad-ptr.errors > tests/userprog/create-bad-ptr.output
# perl -I../.. ../../tests/userprog/create-bad-ptr.ck tests/userprog/create-bad-ptr tests/userprog/create-bad-ptr.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/create-long:create-long --swap-disk=4 -- -q   -f run create-long < /dev/null 2> tests/userprog/create-long.errors > tests/userprog/create-long.output
# perl -I../.. ../../tests/userprog/create-long.ck tests/userprog/create-long tests/userprog/create-long.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/create-exists:create-exists --swap-disk=4 -- -q   -f run create-exists < /dev/null 2> tests/userprog/create-exists.errors > tests/userprog/create-exists.output
# perl -I../.. ../../tests/userprog/create-exists.ck tests/userprog/create-exists tests/userprog/create-exists.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/create-bound:create-bound --swap-disk=4 -- -q   -f run create-bound < /dev/null 2> tests/userprog/create-bound.errors > tests/userprog/create-bound.output
# perl -I../.. ../../tests/userprog/create-bound.ck tests/userprog/create-bound tests/userprog/create-bound.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/open-normal:open-normal -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run open-normal < /dev/null 2> tests/userprog/open-normal.errors > tests/userprog/open-normal.output
# perl -I../.. ../../tests/userprog/open-normal.ck tests/userprog/open-normal tests/userprog/open-normal.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/open-missing:open-missing --swap-disk=4 -- -q   -f run open-missing < /dev/null 2> tests/userprog/open-missing.errors > tests/userprog/open-missing.output
# perl -I../.. ../../tests/userprog/open-missing.ck tests/userprog/open-missing tests/userprog/open-missing.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/open-boundary:open-boundary -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run open-boundary < /dev/null 2> tests/userprog/open-boundary.errors > tests/userprog/open-boundary.output
# perl -I../.. ../../tests/userprog/open-boundary.ck tests/userprog/open-boundary tests/userprog/open-boundary.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/open-empty:open-empty --swap-disk=4 -- -q   -f run open-empty < /dev/null 2> tests/userprog/open-empty.errors > tests/userprog/open-empty.output
# perl -I../.. ../../tests/userprog/open-empty.ck tests/userprog/open-empty tests/userprog/open-empty.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/open-null:open-null --swap-disk=4 -- -q   -f run open-null < /dev/null 2> tests/userprog/open-null.errors > tests/userprog/open-null.output
# perl -I../.. ../../tests/userprog/open-null.ck tests/userprog/open-null tests/userprog/open-null.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/open-bad-ptr:open-bad-ptr --swap-disk=4 -- -q   -f run open-bad-ptr < /dev/null 2> tests/userprog/open-bad-ptr.errors > tests/userprog/open-bad-ptr.output
# perl -I../.. ../../tests/userprog/open-bad-ptr.ck tests/userprog/open-bad-ptr tests/userprog/open-bad-ptr.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/open-twice:open-twice -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run open-twice < /dev/null 2> tests/userprog/open-twice.errors > tests/userprog/open-twice.output
# perl -I../.. ../../tests/userprog/open-twice.ck tests/userprog/open-twice tests/userprog/open-twice.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/close-normal:close-normal -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run close-normal < /dev/null 2> tests/userprog/close-normal.errors > tests/userprog/close-normal.output
# perl -I../.. ../../tests/userprog/close-normal.ck tests/userprog/close-normal tests/userprog/close-normal.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/close-twice:close-twice -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run close-twice < /dev/null 2> tests/userprog/close-twice.errors > tests/userprog/close-twice.output
# perl -I../.. ../../tests/userprog/close-twice.ck tests/userprog/close-twice tests/userprog/close-twice.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/close-bad-fd:close-bad-fd --swap-disk=4 -- -q   -f run close-bad-fd < /dev/null 2> tests/userprog/close-bad-fd.errors > tests/userprog/close-bad-fd.output
# perl -I../.. ../../tests/userprog/close-bad-fd.ck tests/userprog/close-bad-fd tests/userprog/close-bad-fd.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/read-normal:read-normal -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run read-normal < /dev/null 2> tests/userprog/read-normal.errors > tests/userprog/read-normal.output
# perl -I../.. ../../tests/userprog/read-normal.ck tests/userprog/read-normal tests/userprog/read-normal.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/read-bad-ptr:read-bad-ptr -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run read-bad-ptr < /dev/null 2> tests/userprog/read-bad-ptr.errors > tests/userprog/read-bad-ptr.output
# perl -I../.. ../../tests/userprog/read-bad-ptr.ck tests/userprog/read-bad-ptr tests/userprog/read-bad-ptr.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/read-boundary:read-boundary -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run read-boundary < /dev/null 2> tests/userprog/read-boundary.errors > tests/userprog/read-boundary.output
# perl -I../.. ../../tests/userprog/read-boundary.ck tests/userprog/read-boundary tests/userprog/read-boundary.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/read-zero:read-zero -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run read-zero < /dev/null 2> tests/userprog/read-zero.errors > tests/userprog/read-zero.output
# perl -I../.. ../../tests/userprog/read-zero.ck tests/userprog/read-zero tests/userprog/read-zero.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/read-stdout:read-stdout --swap-disk=4 -- -q   -f run read-stdout < /dev/null 2> tests/userprog/read-stdout.errors > tests/userprog/read-stdout.output
# perl -I../.. ../../tests/userprog/read-stdout.ck tests/userprog/read-stdout tests/userprog/read-stdout.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/read-bad-fd:read-bad-fd --swap-disk=4 -- -q   -f run read-bad-fd < /dev/null 2> tests/userprog/read-bad-fd.errors > tests/userprog/read-bad-fd.output
# perl -I../.. ../../tests/userprog/read-bad-fd.ck tests/userprog/read-bad-fd tests/userprog/read-bad-fd.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/write-normal:write-normal -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run write-normal < /dev/null 2> tests/userprog/write-normal.errors > tests/userprog/write-normal.output
# perl -I../.. ../../tests/userprog/write-normal.ck tests/userprog/write-normal tests/userprog/write-normal.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/write-bad-ptr:write-bad-ptr -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run write-bad-ptr < /dev/null 2> tests/userprog/write-bad-ptr.errors > tests/userprog/write-bad-ptr.output
# perl -I../.. ../../tests/userprog/write-bad-ptr.ck tests/userprog/write-bad-ptr tests/userprog/write-bad-ptr.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/write-boundary:write-boundary -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run write-boundary < /dev/null 2> tests/userprog/write-boundary.errors > tests/userprog/write-boundary.output
# perl -I../.. ../../tests/userprog/write-boundary.ck tests/userprog/write-boundary tests/userprog/write-boundary.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/write-zero:write-zero -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run write-zero < /dev/null 2> tests/userprog/write-zero.errors > tests/userprog/write-zero.output
# perl -I../.. ../../tests/userprog/write-zero.ck tests/userprog/write-zero tests/userprog/write-zero.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/write-stdin:write-stdin --swap-disk=4 -- -q   -f run write-stdin < /dev/null 2> tests/userprog/write-stdin.errors > tests/userprog/write-stdin.output
# perl -I../.. ../../tests/userprog/write-stdin.ck tests/userprog/write-stdin tests/userprog/write-stdin.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/write-bad-fd:write-bad-fd --swap-disk=4 -- -q   -f run write-bad-fd < /dev/null 2> tests/userprog/write-bad-fd.errors > tests/userprog/write-bad-fd.output
# perl -I../.. ../../tests/userprog/write-bad-fd.ck tests/userprog/write-bad-fd tests/userprog/write-bad-fd.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/exec-once:exec-once -p tests/userprog/child-simple:child-simple --swap-disk=4 -- -q   -f run exec-once < /dev/null 2> tests/userprog/exec-once.errors > tests/userprog/exec-once.output
# perl -I../.. ../../tests/userprog/exec-once.ck tests/userprog/exec-once tests/userprog/exec-once.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/exec-arg:exec-arg -p tests/userprog/child-args:child-args --swap-disk=4 -- -q   -f run exec-arg < /dev/null 2> tests/userprog/exec-arg.errors > tests/userprog/exec-arg.output
# perl -I../.. ../../tests/userprog/exec-arg.ck tests/userprog/exec-arg tests/userprog/exec-arg.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/exec-missing:exec-missing --swap-disk=4 -- -q   -f run exec-missing < /dev/null 2> tests/userprog/exec-missing.errors > tests/userprog/exec-missing.output
# perl -I../.. ../../tests/userprog/exec-missing.ck tests/userprog/exec-missing tests/userprog/exec-missing.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/exec-bad-ptr:exec-bad-ptr --swap-disk=4 -- -q   -f run exec-bad-ptr < /dev/null 2> tests/userprog/exec-bad-ptr.errors > tests/userprog/exec-bad-ptr.output
# perl -I../.. ../../tests/userprog/exec-bad-ptr.ck tests/userprog/exec-bad-ptr tests/userprog/exec-bad-ptr.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/wait-bad-pid:wait-bad-pid --swap-disk=4 -- -q   -f run wait-bad-pid < /dev/null 2> tests/userprog/wait-bad-pid.errors > tests/userprog/wait-bad-pid.output
# perl -I../.. ../../tests/userprog/wait-bad-pid.ck tests/userprog/wait-bad-pid tests/userprog/wait-bad-pid.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/rox-simple:rox-simple --swap-disk=4 -- -q   -f run rox-simple < /dev/null 2> tests/userprog/rox-simple.errors > tests/userprog/rox-simple.output
# perl -I../.. ../../tests/userprog/rox-simple.ck tests/userprog/rox-simple tests/userprog/rox-simple.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/bad-read:bad-read --swap-disk=4 -- -q   -f run bad-read < /dev/null 2> tests/userprog/bad-read.errors > tests/userprog/bad-read.output
# perl -I../.. ../../tests/userprog/bad-read.ck tests/userprog/bad-read tests/userprog/bad-read.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/bad-write:bad-write --swap-disk=4 -- -q   -f run bad-write < /dev/null 2> tests/userprog/bad-write.errors > tests/userprog/bad-write.output
# perl -I../.. ../../tests/userprog/bad-write.ck tests/userprog/bad-write tests/userprog/bad-write.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/bad-read2:bad-read2 --swap-disk=4 -- -q   -f run bad-read2 < /dev/null 2> tests/userprog/bad-read2.errors > tests/userprog/bad-read2.output
# perl -I../.. ../../tests/userprog/bad-read2.ck tests/userprog/bad-read2 tests/userprog/bad-read2.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/bad-write2:bad-write2 --swap-disk=4 -- -q   -f run bad-write2 < /dev/null 2> tests/userprog/bad-write2.errors > tests/userprog/bad-write2.output
# perl -I../.. ../../tests/userprog/bad-write2.ck tests/userprog/bad-write2 tests/userprog/bad-write2.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/bad-jump:bad-jump --swap-disk=4 -- -q   -f run bad-jump < /dev/null 2> tests/userprog/bad-jump.errors > tests/userprog/bad-jump.output
# perl -I../.. ../../tests/userprog/bad-jump.ck tests/userprog/bad-jump tests/userprog/bad-jump.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/bad-jump2:bad-jump2 --swap-disk=4 -- -q   -f run bad-jump2 < /dev/null 2> tests/userprog/bad-jump2.errors > tests/userprog/bad-jump2.output
# perl -I../.. ../../tests/userprog/bad-jump2.ck tests/userprog/bad-jump2 tests/userprog/bad-jump2.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/lg-create:lg-create --swap-disk=4 -- -q   -f run lg-create < /dev/null 2> tests/filesys/base/lg-create.errors > tests/filesys/base/lg-create.output
# perl -I../.. ../../tests/filesys/base/lg-create.ck tests/filesys/base/lg-create tests/filesys/base/lg-create.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/lg-full:lg-full --swap-disk=4 -- -q   -f run lg-full < /dev/null 2> tests/filesys/base/lg-full.errors > tests/filesys/base/lg-full.output
# perl -I../.. ../../tests/filesys/base/lg-full.ck tests/filesys/base/lg-full tests/filesys/base/lg-full.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/lg-random:lg-random --swap-disk=4 -- -q   -f run lg-random < /dev/null 2> tests/filesys/base/lg-random.errors > tests/filesys/base/lg-random.output
# perl -I../.. ../../tests/filesys/base/lg-random.ck tests/filesys/base/lg-random tests/filesys/base/lg-random.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/lg-seq-block:lg-seq-block --swap-disk=4 -- -q   -f run lg-seq-block < /dev/null 2> tests/filesys/base/lg-seq-block.errors > tests/filesys/base/lg-seq-block.output
# perl -I../.. ../../tests/filesys/base/lg-seq-block.ck tests/filesys/base/lg-seq-block tests/filesys/base/lg-seq-block.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/lg-seq-random:lg-seq-random --swap-disk=4 -- -q   -f run lg-seq-random < /dev/null 2> tests/filesys/base/lg-seq-random.errors > tests/filesys/base/lg-seq-random.output
# perl -I../.. ../../tests/filesys/base/lg-seq-random.ck tests/filesys/base/lg-seq-random tests/filesys/base/lg-seq-random.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/sm-create:sm-create --swap-disk=4 -- -q   -f run sm-create < /dev/null 2> tests/filesys/base/sm-create.errors > tests/filesys/base/sm-create.output
# perl -I../.. ../../tests/filesys/base/sm-create.ck tests/filesys/base/sm-create tests/filesys/base/sm-create.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/sm-full:sm-full --swap-disk=4 -- -q   -f run sm-full < /dev/null 2> tests/filesys/base/sm-full.errors > tests/filesys/base/sm-full.output
# perl -I../.. ../../tests/filesys/base/sm-full.ck tests/filesys/base/sm-full tests/filesys/base/sm-full.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/sm-random:sm-random --swap-disk=4 -- -q   -f run sm-random < /dev/null 2> tests/filesys/base/sm-random.errors > tests/filesys/base/sm-random.output
# perl -I../.. ../../tests/filesys/base/sm-random.ck tests/filesys/base/sm-random tests/filesys/base/sm-random.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/sm-seq-block:sm-seq-block --swap-disk=4 -- -q   -f run sm-seq-block < /dev/null 2> tests/filesys/base/sm-seq-block.errors > tests/filesys/base/sm-seq-block.output
# perl -I../.. ../../tests/filesys/base/sm-seq-block.ck tests/filesys/base/sm-seq-block tests/filesys/base/sm-seq-block.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/sm-seq-random:sm-seq-random --swap-disk=4 -- -q   -f run sm-seq-random < /dev/null 2> tests/filesys/base/sm-seq-random.errors > tests/filesys/base/sm-seq-random.output
# perl -I../.. ../../tests/filesys/base/sm-seq-random.ck tests/filesys/base/sm-seq-random tests/filesys/base/sm-seq-random.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/syn-remove:syn-remove --swap-disk=4 -- -q   -f run syn-remove < /dev/null 2> tests/filesys/base/syn-remove.errors > tests/filesys/base/syn-remove.output
# perl -I../.. ../../tests/filesys/base/syn-remove.ck tests/filesys/base/syn-remove tests/filesys/base/syn-remove.result

# # Project 2 - User program - syscall tests that use fork
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/fork-once:fork-once --swap-disk=4 -- -q   -f run fork-once < /dev/null 2> tests/userprog/fork-once.errors > tests/userprog/fork-once.output
# perl -I../.. ../../tests/userprog/fork-once.ck tests/userprog/fork-once tests/userprog/fork-once.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/fork-multiple:fork-multiple --swap-disk=4 -- -q   -f run fork-multiple < /dev/null 2> tests/userprog/fork-multiple.errors > tests/userprog/fork-multiple.output
# perl -I../.. ../../tests/userprog/fork-multiple.ck tests/userprog/fork-multiple tests/userprog/fork-multiple.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/fork-recursive:fork-recursive --swap-disk=4 -- -q   -f run fork-recursive < /dev/null 2> tests/userprog/fork-recursive.errors > tests/userprog/fork-recursive.output
# perl -I../.. ../../tests/userprog/fork-recursive.ck tests/userprog/fork-recursive tests/userprog/fork-recursive.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/fork-read:fork-read -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run fork-read < /dev/null 2> tests/userprog/fork-read.errors > tests/userprog/fork-read.output
# perl -I../.. ../../tests/userprog/fork-read.ck tests/userprog/fork-read tests/userprog/fork-read.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/fork-close:fork-close -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run fork-close < /dev/null 2> tests/userprog/fork-close.errors > tests/userprog/fork-close.output
# perl -I../.. ../../tests/userprog/fork-close.ck tests/userprog/fork-close tests/userprog/fork-close.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/fork-boundary:fork-boundary --swap-disk=4 -- -q   -f run fork-boundary < /dev/null 2> tests/userprog/fork-boundary.errors > tests/userprog/fork-boundary.output
# perl -I../.. ../../tests/userprog/fork-boundary.ck tests/userprog/fork-boundary tests/userprog/fork-boundary.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/exec-boundary:exec-boundary -p tests/userprog/child-simple:child-simple --swap-disk=4 -- -q   -f run exec-boundary < /dev/null 2> tests/userprog/exec-boundary.errors > tests/userprog/exec-boundary.output
# perl -I../.. ../../tests/userprog/exec-boundary.ck tests/userprog/exec-boundary tests/userprog/exec-boundary.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/exec-read:exec-read -p ../../tests/userprog/sample.txt:sample.txt -p tests/userprog/child-read:child-read --swap-disk=4 -- -q   -f run exec-read < /dev/null 2> tests/userprog/exec-read.errors > tests/userprog/exec-read.output
# perl -I../.. ../../tests/userprog/exec-read.ck tests/userprog/exec-read tests/userprog/exec-read.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/wait-simple:wait-simple -p tests/userprog/child-simple:child-simple --swap-disk=4 -- -q   -f run wait-simple < /dev/null 2> tests/userprog/wait-simple.errors > tests/userprog/wait-simple.output
# perl -I../.. ../../tests/userprog/wait-simple.ck tests/userprog/wait-simple tests/userprog/wait-simple.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/wait-twice:wait-twice -p tests/userprog/child-simple:child-simple --swap-disk=4 -- -q   -f run wait-twice < /dev/null 2> tests/userprog/wait-twice.errors > tests/userprog/wait-twice.output
# perl -I../.. ../../tests/userprog/wait-twice.ck tests/userprog/wait-twice tests/userprog/wait-twice.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/wait-killed:wait-killed -p tests/userprog/child-bad:child-bad --swap-disk=4 -- -q   -f run wait-killed < /dev/null 2> tests/userprog/wait-killed.errors > tests/userprog/wait-killed.output
# perl -I../.. ../../tests/userprog/wait-killed.ck tests/userprog/wait-killed tests/userprog/wait-killed.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/multi-recurse:multi-recurse --swap-disk=4 -- -q   -f run 'multi-recurse 15' < /dev/null 2> tests/userprog/multi-recurse.errors > tests/userprog/multi-recurse.output
# perl -I../.. ../../tests/userprog/multi-recurse.ck tests/userprog/multi-recurse tests/userprog/multi-recurse.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/multi-child-fd:multi-child-fd -p ../../tests/userprog/sample.txt:sample.txt -p tests/userprog/child-close:child-close --swap-disk=4 -- -q   -f run multi-child-fd < /dev/null 2> tests/userprog/multi-child-fd.errors > tests/userprog/multi-child-fd.output
# perl -I../.. ../../tests/userprog/multi-child-fd.ck tests/userprog/multi-child-fd tests/userprog/multi-child-fd.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/rox-child:rox-child -p tests/userprog/child-rox:child-rox --swap-disk=4 -- -q   -f run rox-child < /dev/null 2> tests/userprog/rox-child.errors > tests/userprog/rox-child.output
# perl -I../.. ../../tests/userprog/rox-child.ck tests/userprog/rox-child tests/userprog/rox-child.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/rox-multichild:rox-multichild -p tests/userprog/child-rox:child-rox --swap-disk=4 -- -q   -f run rox-multichild < /dev/null 2> tests/userprog/rox-multichild.errors > tests/userprog/rox-multichild.output
# perl -I../.. ../../tests/userprog/rox-multichild.ck tests/userprog/rox-multichild tests/userprog/rox-multichild.result
# pintos -v -k -T 300 -m 20   --fs-disk=10 -p tests/filesys/base/syn-read:syn-read -p tests/filesys/base/child-syn-read:child-syn-read --swap-disk=4 -- -q   -f run syn-read < /dev/null 2> tests/filesys/base/syn-read.errors > tests/filesys/base/syn-read.output
# perl -I../.. ../../tests/filesys/base/syn-read.ck tests/filesys/base/syn-read tests/filesys/base/syn-read.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/filesys/base/syn-write:syn-write -p tests/filesys/base/child-syn-wrt:child-syn-wrt --swap-disk=4 -- -q   -f run syn-write < /dev/null 2> tests/filesys/base/syn-write.errors > tests/filesys/base/syn-write.output
# perl -I../.. ../../tests/filesys/base/syn-write.ck tests/filesys/base/syn-write tests/filesys/base/syn-write.result

# # VM - ?
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/cow/cow-simple:cow-simple --swap-disk=4 -- -q   -f run cow-simple < /dev/null 2> tests/vm/cow/cow-simple.errors > tests/vm/cow/cow-simple.output
# perl -I../.. ../../tests/vm/cow/cow-simple.ck tests/vm/cow/cow-simple tests/vm/cow/cow-simple.result

# # VM
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/pt-grow-stack:pt-grow-stack --swap-disk=4 -- -q   -f run pt-grow-stack < /dev/null 2> tests/vm/pt-grow-stack.errors > tests/vm/pt-grow-stack.output
# perl -I../.. ../../tests/vm/pt-grow-stack.ck tests/vm/pt-grow-stack tests/vm/pt-grow-stack.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/pt-grow-bad:pt-grow-bad --swap-disk=4 -- -q   -f run pt-grow-bad < /dev/null 2> tests/vm/pt-grow-bad.errors > tests/vm/pt-grow-bad.output
# perl -I../.. ../../tests/vm/pt-grow-bad.ck tests/vm/pt-grow-bad tests/vm/pt-grow-bad.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/pt-big-stk-obj:pt-big-stk-obj --swap-disk=4 -- -q   -f run pt-big-stk-obj < /dev/null 2> tests/vm/pt-big-stk-obj.errors > tests/vm/pt-big-stk-obj.output
# perl -I../.. ../../tests/vm/pt-big-stk-obj.ck tests/vm/pt-big-stk-obj tests/vm/pt-big-stk-obj.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/pt-bad-addr:pt-bad-addr --swap-disk=4 -- -q   -f run pt-bad-addr < /dev/null 2> tests/vm/pt-bad-addr.errors > tests/vm/pt-bad-addr.output
# perl -I../.. ../../tests/vm/pt-bad-addr.ck tests/vm/pt-bad-addr tests/vm/pt-bad-addr.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/pt-bad-read:pt-bad-read -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run pt-bad-read < /dev/null 2> tests/vm/pt-bad-read.errors > tests/vm/pt-bad-read.output
# perl -I../.. ../../tests/vm/pt-bad-read.ck tests/vm/pt-bad-read tests/vm/pt-bad-read.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/pt-write-code:pt-write-code --swap-disk=4 -- -q   -f run pt-write-code < /dev/null 2> tests/vm/pt-write-code.errors > tests/vm/pt-write-code.output
# perl -I../.. ../../tests/vm/pt-write-code.ck tests/vm/pt-write-code tests/vm/pt-write-code.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/pt-write-code2:pt-write-code2 -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run pt-write-code2 < /dev/null 2> tests/vm/pt-write-code2.errors > tests/vm/pt-write-code2.output
# perl -I../.. ../../tests/vm/pt-write-code2.ck tests/vm/pt-write-code2 tests/vm/pt-write-code2.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/pt-grow-stk-sc:pt-grow-stk-sc --swap-disk=4 -- -q   -f run pt-grow-stk-sc < /dev/null 2> tests/vm/pt-grow-stk-sc.errors > tests/vm/pt-grow-stk-sc.output
# perl -I../.. ../../tests/vm/pt-grow-stk-sc.ck tests/vm/pt-grow-stk-sc tests/vm/pt-grow-stk-sc.result
# pintos -v -k -T 300 -m 20   --fs-disk=10 -p tests/vm/page-linear:page-linear --swap-disk=4 -- -q   -f run page-linear < /dev/null 2> tests/vm/page-linear.errors > tests/vm/page-linear.output
# perl -I../.. ../../tests/vm/page-linear.ck tests/vm/page-linear tests/vm/page-linear.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/page-parallel:page-parallel -p tests/vm/child-linear:child-linear --swap-disk=4 -- -q   -f run page-parallel < /dev/null 2> tests/vm/page-parallel.errors > tests/vm/page-parallel.output
# perl -I../.. ../../tests/vm/page-parallel.ck tests/vm/page-parallel tests/vm/page-parallel.result
pintos -v -k -T 600 -m 20   --fs-disk=10 -p tests/vm/page-merge-seq:page-merge-seq -p tests/vm/child-sort:child-sort --swap-disk=4 -- -q   -f run page-merge-seq < /dev/null 2> tests/vm/page-merge-seq.errors > tests/vm/page-merge-seq.output
perl -I../.. ../../tests/vm/page-merge-seq.ck tests/vm/page-merge-seq tests/vm/page-merge-seq.result
pintos -v -k -T 600 -m 20   --fs-disk=10 -p tests/vm/page-merge-par:page-merge-par -p tests/vm/child-sort:child-sort --swap-disk=10 -- -q   -f run page-merge-par < /dev/null 2> tests/vm/page-merge-par.errors > tests/vm/page-merge-par.output
perl -I../.. ../../tests/vm/page-merge-par.ck tests/vm/page-merge-par tests/vm/page-merge-par.result
pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/page-merge-stk:page-merge-stk -p tests/vm/child-qsort:child-qsort --swap-disk=10 -- -q   -f run page-merge-stk < /dev/null 2> tests/vm/page-merge-stk.errors > tests/vm/page-merge-stk.output
perl -I../.. ../../tests/vm/page-merge-stk.ck tests/vm/page-merge-stk tests/vm/page-merge-stk.result
pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/page-merge-mm:page-merge-mm -p tests/vm/child-qsort-mm:child-qsort-mm --swap-disk=10 -- -q   -f run page-merge-mm < /dev/null 2> tests/vm/page-merge-mm.errors > tests/vm/page-merge-mm.output
perl -I../.. ../../tests/vm/page-merge-mm.ck tests/vm/page-merge-mm tests/vm/page-merge-mm.result
# pintos -v -k -T 600 -m 20   --fs-disk=10 -p tests/vm/page-shuffle:page-shuffle --swap-disk=4 -- -q   -f run page-shuffle < /dev/null 2> tests/vm/page-shuffle.errors > tests/vm/page-shuffle.output
# perl -I../.. ../../tests/vm/page-shuffle.ck tests/vm/page-shuffle tests/vm/page-shuffle.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-read:mmap-read -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-read < /dev/null 2> tests/vm/mmap-read.errors > tests/vm/mmap-read.output
# perl -I../.. ../../tests/vm/mmap-read.ck tests/vm/mmap-read tests/vm/mmap-read.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-close:mmap-close -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-close < /dev/null 2> tests/vm/mmap-close.errors > tests/vm/mmap-close.output
# perl -I../.. ../../tests/vm/mmap-close.ck tests/vm/mmap-close tests/vm/mmap-close.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-unmap:mmap-unmap -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-unmap < /dev/null 2> tests/vm/mmap-unmap.errors > tests/vm/mmap-unmap.output
# perl -I../.. ../../tests/vm/mmap-unmap.ck tests/vm/mmap-unmap tests/vm/mmap-unmap.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-overlap:mmap-overlap -p tests/vm/zeros:zeros --swap-disk=4 -- -q   -f run mmap-overlap < /dev/null 2> tests/vm/mmap-overlap.errors > tests/vm/mmap-overlap.output
# perl -I../.. ../../tests/vm/mmap-overlap.ck tests/vm/mmap-overlap tests/vm/mmap-overlap.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-twice:mmap-twice -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-twice < /dev/null 2> tests/vm/mmap-twice.errors > tests/vm/mmap-twice.output
# perl -I../.. ../../tests/vm/mmap-twice.ck tests/vm/mmap-twice tests/vm/mmap-twice.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-write:mmap-write --swap-disk=4 -- -q   -f run mmap-write < /dev/null 2> tests/vm/mmap-write.errors > tests/vm/mmap-write.output
# perl -I../.. ../../tests/vm/mmap-write.ck tests/vm/mmap-write tests/vm/mmap-write.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-ro:mmap-ro -p ../../tests/vm/large.txt:large.txt --swap-disk=4 -- -q   -f run mmap-ro < /dev/null 2> tests/vm/mmap-ro.errors > tests/vm/mmap-ro.output
# perl -I../.. ../../tests/vm/mmap-ro.ck tests/vm/mmap-ro tests/vm/mmap-ro.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-exit:mmap-exit -p tests/vm/child-mm-wrt:child-mm-wrt --swap-disk=4 -- -q   -f run mmap-exit < /dev/null 2> tests/vm/mmap-exit.errors > tests/vm/mmap-exit.output
# perl -I../.. ../../tests/vm/mmap-exit.ck tests/vm/mmap-exit tests/vm/mmap-exit.result
# pintos -v -k -T 600 -m 20   --fs-disk=10 -p tests/vm/mmap-shuffle:mmap-shuffle --swap-disk=4 -- -q   -f run mmap-shuffle < /dev/null 2> tests/vm/mmap-shuffle.errors > tests/vm/mmap-shuffle.output
# perl -I../.. ../../tests/vm/mmap-shuffle.ck tests/vm/mmap-shuffle tests/vm/mmap-shuffle.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-bad-fd:mmap-bad-fd --swap-disk=4 -- -q   -f run mmap-bad-fd < /dev/null 2> tests/vm/mmap-bad-fd.errors > tests/vm/mmap-bad-fd.output
# perl -I../.. ../../tests/vm/mmap-bad-fd.ck tests/vm/mmap-bad-fd tests/vm/mmap-bad-fd.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-clean:mmap-clean -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-clean < /dev/null 2> tests/vm/mmap-clean.errors > tests/vm/mmap-clean.output
# perl -I../.. ../../tests/vm/mmap-clean.ck tests/vm/mmap-clean tests/vm/mmap-clean.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-inherit:mmap-inherit -p ../../tests/vm/sample.txt:sample.txt -p tests/vm/child-inherit:child-inherit --swap-disk=4 -- -q   -f run mmap-inherit < /dev/null 2> tests/vm/mmap-inherit.errors > tests/vm/mmap-inherit.output
# perl -I../.. ../../tests/vm/mmap-inherit.ck tests/vm/mmap-inherit tests/vm/mmap-inherit.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-misalign:mmap-misalign -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-misalign < /dev/null 2> tests/vm/mmap-misalign.errors > tests/vm/mmap-misalign.output
# perl -I../.. ../../tests/vm/mmap-misalign.ck tests/vm/mmap-misalign tests/vm/mmap-misalign.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-null:mmap-null -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-null < /dev/null 2> tests/vm/mmap-null.errors > tests/vm/mmap-null.output
# perl -I../.. ../../tests/vm/mmap-null.ck tests/vm/mmap-null tests/vm/mmap-null.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-over-code:mmap-over-code -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-over-code < /dev/null 2> tests/vm/mmap-over-code.errors > tests/vm/mmap-over-code.output
# perl -I../.. ../../tests/vm/mmap-over-code.ck tests/vm/mmap-over-code tests/vm/mmap-over-code.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-over-data:mmap-over-data -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-over-data < /dev/null 2> tests/vm/mmap-over-data.errors > tests/vm/mmap-over-data.output
# perl -I../.. ../../tests/vm/mmap-over-data.ck tests/vm/mmap-over-data tests/vm/mmap-over-data.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-over-stk:mmap-over-stk -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-over-stk < /dev/null 2> tests/vm/mmap-over-stk.errors > tests/vm/mmap-over-stk.output
# perl -I../.. ../../tests/vm/mmap-over-stk.ck tests/vm/mmap-over-stk tests/vm/mmap-over-stk.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-remove:mmap-remove -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-remove < /dev/null 2> tests/vm/mmap-remove.errors > tests/vm/mmap-remove.output
# perl -I../.. ../../tests/vm/mmap-remove.ck tests/vm/mmap-remove tests/vm/mmap-remove.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-zero:mmap-zero --swap-disk=4 -- -q   -f run mmap-zero < /dev/null 2> tests/vm/mmap-zero.errors > tests/vm/mmap-zero.output
# perl -I../.. ../../tests/vm/mmap-zero.ck tests/vm/mmap-zero tests/vm/mmap-zero.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-bad-fd2:mmap-bad-fd2 --swap-disk=4 -- -q   -f run mmap-bad-fd2 < /dev/null 2> tests/vm/mmap-bad-fd2.errors > tests/vm/mmap-bad-fd2.output
# perl -I../.. ../../tests/vm/mmap-bad-fd2.ck tests/vm/mmap-bad-fd2 tests/vm/mmap-bad-fd2.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-bad-fd3:mmap-bad-fd3 --swap-disk=4 -- -q   -f run mmap-bad-fd3 < /dev/null 2> tests/vm/mmap-bad-fd3.errors > tests/vm/mmap-bad-fd3.output
# perl -I../.. ../../tests/vm/mmap-bad-fd3.ck tests/vm/mmap-bad-fd3 tests/vm/mmap-bad-fd3.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-zero-len:mmap-zero-len --swap-disk=4 -- -q   -f run mmap-zero-len < /dev/null 2> tests/vm/mmap-zero-len.errors > tests/vm/mmap-zero-len.output
# perl -I../.. ../../tests/vm/mmap-zero-len.ck tests/vm/mmap-zero-len tests/vm/mmap-zero-len.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-off:mmap-off -p ../../tests/vm/large.txt:large.txt --swap-disk=4 -- -q   -f run mmap-off < /dev/null 2> tests/vm/mmap-off.errors > tests/vm/mmap-off.output
# perl -I../.. ../../tests/vm/mmap-off.ck tests/vm/mmap-off tests/vm/mmap-off.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-bad-off:mmap-bad-off -p ../../tests/vm/large.txt:large.txt --swap-disk=4 -- -q   -f run mmap-bad-off < /dev/null 2> tests/vm/mmap-bad-off.errors > tests/vm/mmap-bad-off.output
# perl -I../.. ../../tests/vm/mmap-bad-off.ck tests/vm/mmap-bad-off tests/vm/mmap-bad-off.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/mmap-kernel:mmap-kernel -p ../../tests/vm/sample.txt:sample.txt --swap-disk=4 -- -q   -f run mmap-kernel < /dev/null 2> tests/vm/mmap-kernel.errors > tests/vm/mmap-kernel.output
# perl -I../.. ../../tests/vm/mmap-kernel.ck tests/vm/mmap-kernel tests/vm/mmap-kernel.result
# pintos -v -k -T 600 -m 20   --fs-disk=10 -p tests/vm/lazy-file:lazy-file -p ../../tests/vm/sample.txt:sample.txt -p ../../tests/vm/small.txt:small.txt --swap-disk=4 -- -q   -f run lazy-file < /dev/null 2> tests/vm/lazy-file.errors > tests/vm/lazy-file.output
# perl -I../.. ../../tests/vm/lazy-file.ck tests/vm/lazy-file tests/vm/lazy-file.result
# pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/vm/lazy-anon:lazy-anon --swap-disk=4 -- -q   -f run lazy-anon < /dev/null 2> tests/vm/lazy-anon.errors > tests/vm/lazy-anon.output
# perl -I../.. ../../tests/vm/lazy-anon.ck tests/vm/lazy-anon tests/vm/lazy-anon.result
# pintos -v -k -T 180 -m 8   --fs-disk=10 -p tests/vm/swap-file:swap-file -p ../../tests/vm/large.txt:large.txt --swap-disk=10 -- -q   -f run swap-file < /dev/null 2> tests/vm/swap-file.errors > tests/vm/swap-file.output
# perl -I../.. ../../tests/vm/swap-file.ck tests/vm/swap-file tests/vm/swap-file.result
# pintos -v -k -T 180 -m 10   --fs-disk=10 -p tests/vm/swap-anon:swap-anon --swap-disk=30 -- -q   -f run swap-anon < /dev/null 2> tests/vm/swap-anon.errors > tests/vm/swap-anon.output
# perl -I../.. ../../tests/vm/swap-anon.ck tests/vm/swap-anon tests/vm/swap-anon.result
# pintos -v -k -T 180 -m 10   --fs-disk=10 -p tests/vm/swap-iter:swap-iter -p ../../tests/vm/large.txt:large.txt --swap-disk=50 -- -q   -f run swap-iter < /dev/null 2> tests/vm/swap-iter.errors > tests/vm/swap-iter.output
# perl -I../.. ../../tests/vm/swap-iter.ck tests/vm/swap-iter tests/vm/swap-iter.result
pintos -v -k -T 600 -m 40   --fs-disk=10 -p tests/vm/swap-fork:swap-fork -p tests/vm/child-swap:child-swap --swap-disk=200 -- -q   -f run swap-fork < /dev/null 2> tests/vm/swap-fork.errors > tests/vm/swap-fork.output
perl -I../.. ../../tests/vm/swap-fork.ck tests/vm/swap-fork tests/vm/swap-fork.result