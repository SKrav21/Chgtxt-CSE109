#!/bin/bash

echo -e "\nTesting your code..."
echo -e "\t* successful compile gets you 9 points"
echo -e "\t* successful check of stdout gets you 4 points for each test"
echo -e "\t* successful check of stderr gets you 1 point  for each test"
echo -e "\t* successful check of rc     gets you 1 point  for each test"
echo -e "\t* (#, #, #) at end of each test indicates pass/fail for stdout, stderr, and rc check, respectively"
echo -e "\nRunning make clean"
make -f makefile clean
echo -e "\nRunning make chgTxt"
make chgTxt
rc=$?
points=0
if [[ $rc -eq 0 ]]; then
  points=$((points + 9)) 
  tests=( "-x <0.in"
          "-line <0.in"
          "<0.in"
          "-t <0.in"
          "-w <0.in"
          "-l <0.in"
          "-d <0.in"
          "-t -w -l -d <1.in"
          "-t -w -l -d <2.in"
          "-t -w -l -d <3.in"
          "-t -w -l -d <4.in"
        )
  passed=0
  total=0
  for test in "${tests[@]}"; do
    total=$((total + 1))
    echo -e "\nTest $total with args: $test"
    #./chgTxt ${test//\'/} 2>/tmp/$$.stderr 1>/tmp/$$.stdout
    eval ./chgTxt $test 2>/tmp/$$.stderr 1>/tmp/$$.stdout
    trc=$?
    #./chgTxt_ref "${test//\'/}" 2>/tmp/$$.stderr_ref 1>/tmp/$$.stdout_ref
    eval ./chgTxt_ref $test 2>/tmp/$$.stderr_ref 1>/tmp/$$.stdout_ref
    grc=$?
    diff /tmp/$$.stdout /tmp/$$.stdout_ref 1>/dev/null 2>&1
    orc=$?
    if [[ $orc -ne 0 ]]; then
      orc=1
    fi
    diff /tmp/$$.stderr /tmp/$$.stderr_ref 1>/dev/null 2>&1
    erc=$?
    if [[ $erc -ne 0 ]]; then
      erc=1
    fi
    if [[ $trc -eq $grc ]]; then
      rrc=0
    else
      rrc=1
    fi
    rc=$((orc + erc + rrc))
    if [[ $rc -eq 0 ]]; then
      echo -e "Test $total passed"
      passed=$((passed + 1))
      points=$((points + 6))
    elif [[ $rc -eq 1 && $orc -eq 1 ]]; then  # two tests passed, and it was not the stdout check
      echo -e "Test $total partially passed ($orc, $erc, $rrc)"
      points=$((points + 2))
    elif [[ $rc -eq 1 && $orc -eq 0 ]]; then  # two tests passed, and it was the stdout check
      echo -e "Test $total partially passed ($orc, $erc, $rrc)"
      points=$((points + 5))
    elif [[ $rc -eq 2 && $orc -eq 1 ]]; then  # one test passed, and it was not the stdout check
      echo -e "Test $total partially passed ($orc, $erc, $rrc)"
      points=$((points + 1))
    elif [[ $rc -eq 2 && $orc -eq 0 ]]; then  # one test passed, and it was the stdout check
      echo -e "Test $total partially passed ($orc, $erc, $rrc)"
      points=$((points + 4))
    else
      echo -e "Test $total failed"
    fi
    if [[ $total -eq 99 ]]; then
      exit
    fi
    rm -f /tmp/$$.std* 1>/dev/null 2>&1
  done
  
  if [[ $passed -eq $total ]]; then
    echo -e "\nAll tests passed"
    rc=0
  else
    failed=$((total-passed))
    echo -e "\n$passed tests passed, $failed tests failed"
    rc=$failed
  fi
else
  echo -e "\nCompilation failed"
fi
echo -e "Score $points/75\n"

exit $rc

