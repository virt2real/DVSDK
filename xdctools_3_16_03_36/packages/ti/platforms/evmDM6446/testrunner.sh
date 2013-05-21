#
#  Copyright (c) 2010 by Texas Instruments and others.
#  All rights reserved. This program and the accompanying materials
#  are made available under the terms of the Eclipse Public License v1.0
#  which accompanies this distribution, and is available at
#  http://www.eclipse.org/legal/epl-v10.html
#
#  Contributors:
#      Texas Instruments - initial implementation
#
#

#!/bin/sh
# TODO:
# L - check what happens if sed/grep filter fails
# M - add check for ctrl-C to be interpreted as current rsh command failure
# L - add --exec
# M - add --timeout
# H - cleanup and reorg this file
# H - need something (better) for test setup/teardown in terms of modules, both for single tests and groups of tests
# M - see if pinging is really necessary

# invocation: <this shell> [ execArgs ] exeName [ exeArgs ]
# define additional execArgs in TESTRUNNERARGS var to add/override execArgs

# TODO: extract v from XDCOPTIONS
VERBOSE=$XDCOPTIONS
# VERBOSE=

originalArgs="$@"

targetName=
targetTestAccount="root"
targetTestDir="/home/test"

testRepository="."

targetExeName=
targetExeArgs=

targetNfsTestDir=
toTargetFiles=
fromTargetFiles=
copyLocalFiles=
diffFiles=
sedFilters=
grepFilters=
referenceStdout=

noLoadModules="false"
noPrompting="false"
extraPrompting="false"
noPing="false"

parseArgs() {
    while [ $# -gt 0 ]; do    # Until you run out of parameters . . .
      case "$1" in
        -t|--toTargetFile)
                  FILE="$2"
                  shift
                  toTargetFiles="$toTargetFiles $FILE"
                  ;;
        -a|--targetNfsTestDir)
                  targetNfsTestDir="$2"
                  shift
                  ;;
        -f|--fromTargetFile)
                  fromTargetFiles="$fromTargetFiles $2"
                  shift
                  ;;
        -c|--copyLocalFile)
                  FILE="$2"
                  shift
                  copyLocalFiles="$copyLocalFiles $FILE"
                  ;;
        -d|--diffFiles)
                  diffFiles="$diffFiles $2:$3"
                  shift
                  shift              
                  ;;
        -s|--sedFilter)
                  sedFilters="$sedFilters $2"
                  shift              
                  ;;
        -g|--grepFilter)
                  grepFilters="$grepFilters $2"
                  shift              
                  ;;
        -o|--referenceStdout)
                  referenceStdout="$2"
                  shift              
                  ;;
        -r|--testRepository)
                  testRepository="$2"
                  shift
                  ;;                  
        -n|--targetName)
                  targetName="$2"
                  shift
                  ;;              
        --targetTestAccount)
                  targetTestAccount="$2"
                  shift
                  ;;              
        --targetTestDir)
                  targetTestDir="$2"
                  shift
                  ;;              
        --noLoadModules)
                  noLoadModules="true"
                  ;;              
        --noPrompting)
                  noPrompting="true"
                  ;;              
        --extraPrompting)
                  extraPrompting="true"
                  ;;              
        --noPing)
                  noPing="true"
                  ;;              
        *) 
                  if [ -z $targetExeFile ] ; then
                      break
                  else
                      writeErr "testrunner> Invalid argument: $1"
                      showUsage writeErr
                      return 1
                  fi
                  ;;
      esac
      shift       # Check next set of parameters.
    done
    if [ -z $targetExeFile ] ; then
        targetExeFile="$1"
        shift
        targetExeArgs="$@"
    fi        
    return 0
}

testLogActive=0

writeLog() {
    if [ $testLogActive -eq 1 ] ; then echo "$@" >>test.log ; fi
    if [ "$VERBOSE" == "v" ]; then echo "$@" >&2 ; fi
}    
writeLogOnly() {
    if [ $testLogActive -eq 1 ] ; then 
        echo "$@" >>test.log 
    else
        echo "$@" >&2 
    fi
}    
writeErr() {
    if [ $testLogActive -eq 1 ] ; then echo "$@" >>test.log ; fi
    echo "$@" >&2
}    
writeTerm() {
    echo "$@" >&2
}    

showUsage() {
    wrCmd=$1
    $wrCmd "  Testrunner ($0) was invoked with following args: "
    $wrCmd "  $originalArgs"
    if [ ! -z "$TESTRUNNERARGS" ] ; then 
        $wrCmd "  Additional args specified in envvar TESTRUNNERARGS were: $TESTRUNNERARGS"
    fi
    $wrCmd "  Testrunner syntax is: testrunner.sh [ execArgs ] targetExe [ args ]"
    $wrCmd "  where allowed execArgs are:"
    $wrCmd "    -n|--targetName     name|IP: network name or IP address of test board"
    $wrCmd "    -r|--testRepository dir: dir to place all tests and logs, otherwise all"
    $wrCmd "                             (tests and logs are in <cur pkg dir>/testruns/)"
    $wrCmd "    -a|--targetNfsTestDir dir: if specified, test files will be [r]copied to and"
    $wrCmd "                        from this dir instead of the default one;"
    $wrCmd "                        example: --targetNfsTestDir root@myboard:/home/test"
    $wrCmd "                        example: --targetNfsTestDir sagebrush:/exports/test"
    $wrCmd "    -t|--toTargetFile   file: file to copy to target before test run"
    $wrCmd "    -f|--fromTargetFile file: file to copied to target after test run"
    $wrCmd "    -c|--copyLocalFile  file: file to copy to host test dir for diffing"
    $wrCmd "    -d|--diffFiles      file1 file2: files from host test dir to diff"
    $wrCmd "    -s|--sedFilter      regExp: filter target stdout with sed, e.g. 's/./x/g'"
    $wrCmd "    -g|--grepFilter     regExp: filter target stdout with grep -v, e.g. 'XXX'"
    $wrCmd "    -o|--referenceStdout file: compare (filtered) target stdout with file"
    $wrCmd "    --targetTestAccount name: user on target for rshing tests (default: root)"
    $wrCmd "    --targetTestDir     dir: target test dir (default:/home/test)"
    $wrCmd "    --noLoadModules     : do not load/unload kernel modules for each test"
    $wrCmd "    --noPing            : do not ping the target for aliveness at start"
    $wrCmd "    --noPrompting       : do not ask to repeat test on connection failure"
    $wrCmd "    --extraPrompting    : ask to repeat test even on non-connection failure"
    $wrCmd "  All file paths are relative to the package base dir."
    $wrCmd "  Diff works only on files in the local (host) test dir."
    $wrCmd "  Additional execArgs can be specified in envvar TESTRUNNERARGS,"
    $wrCmd "    e.g. TESTRUNNERARGS='-n myboard --noLoadModules'"
    $wrCmd "  All tests steps are logged in <test directory>/test.log."
    $wrCmd "  To print all log information as test goes, set XDCOPTIONS envvar to 'v'"
}

parseArgs "$@"
parseArgs ${TESTRUNNERARGS#1}  # make spaces arg delimiters
if [ $? -ne 0 ] ; then         # if nonzero, there was error in TESTRUNNERARGS
    exit 255
fi

if [ ! -f "$targetExeFile" ]; then
    if [ "${targetExeFile:0:1}" == "-" ] ; then
        writeErr "Error: invalid option $targetExeFile."
    else
        writeErr "Error: Target executable $targetExeFile does not exist!"
        writeErr "       (or you passed an incorrect option)"
    fi
    showUsage writeErr
    exit 255
fi

targetExeName="`basename $targetExeFile`"
testName="$targetExeName"  # todo: support testSuffix

if [ $testRepository == "." ] ; then
    localTestDir="./testruns/$testName"   
    pathToPackageBaseDir="../.."
else
    pathToPackageBaseDir=`pwd`
    mkdir -p $testRepository
    cd $testRepository
    testRepository=`pwd`
    cd $pathToPackageBaseDir
    localTestDir="$testRepository/`xdcdir .`/$testName"
fi    
        
toTargetFiles="$targetExeFile $toTargetFiles"

rm -rf $localTestDir
mkdir -p $localTestDir
cd $localTestDir
testLogActive=1




# begin output. writeErr means output to log and to terminal unconditionally
# where writeLog means output to log and to terminal only if verbose mode
# terminal is stderr -- assuming that stderr isn't redirected.

writeErr
writeErr "testrunner> Test [$testName] execution begins at `date`, logged in `pwd`/test.log" 
writeLog "testrunner> Test current directory is `pwd`"
writeLogOnly
# writeLog "testrunner> Test script invoked as: $0 $originalArgs"
# writeLog "testrunner> Testrunner additional args in envvar TESTRUNNERARGS: $TESTRUNNERARGS"
writeLogOnly "testrunner> Testrunner script arguments and usage reminder (FYI):"
showUsage writeLogOnly
writeLogOnly 

if [ -z $targetName ] ; then
    targetName="146.252.161.12"
    writeErr "testrunner> Warning: -n|--targetName name/IP option not specified; defaulting to target name/address '$targetName'. (Note: you can define TESTRUNNERARGS='-n myboard' envvar)"
    writeErr 
fi 

writeLog "testrunner> test param targetName = $targetName"
writeLog "testrunner> test param targetTestAccount = $targetTestAccount"
writeLog "testrunner> test param targetTestDir = $targetTestDir"
writeLog "testrunner> test param targetNfsTestDir = $targetNfsTestDir"
writeLog "testrunner> test param targetExeName = $targetExeName"
writeLog "testrunner> test param targetExeArgs = $targetExeArgs"
writeLog "testrunner> test param toTargetFiles = $toTargetFiles"
writeLog "testrunner> test param fromTargetFiles = $fromTargetFiles"
writeLog "testrunner> test param copyLocalFiles = $copyLocalFiles"
writeLog "testrunner> test param diffFiles = $diffFiles"
writeLog "testrunner> test param sedFilters = $sedFilters"
writeLog "testrunner> test param grepFilters = $grepFilters"
writeLog "testrunner> test param referenceStdout = $referenceStdout"
writeLog "testrunner> test param noLoadModules = $noLoadModules"
writeLog "testrunner> test param noPing = $noPing"
writeLog "testrunner> test param noPrompting = $noPrompting"
writeLog "testrunner> test param extraPrompting = $extraPrompting"
writeLog "testrunner> test param testRepository = $testRepository"
writeLog "testrunner> test current directory = $localTestDir/"


E_TIMEOUT=100

cmdOutFile="cmdout.txt"
cmdRetval=0

runCmd() {
    msg="host> $@"
    writeLog $msg
    cmd="$@"
    $cmd >$cmdOutFile 2>&1
    cmdRetval=$?
    cat $cmdOutFile >>test.log 
    if [ "$VERBOSE" == "v" ]; then cat $cmdOutFile >&2 ; fi
    return $cmdRetval
}

rshOutFile="rshout.txt"
rshRetval=0

runRsh() {
    cmd="rsh -l $targetTestAccount $targetName"
    msg="host> $cmd '$1'"  # $1 is the actual remote command
    writeLog $msg
    cmd="$cmd $1"
    while [ 1 -eq 1 ] ; do
        test >rsh_stdout.txt ; test >rsh_stderr.txt
        if [ "$VERBOSE" == "v" ]; then 
            tail -F -s 0 -q rsh_stdout.txt rsh_stderr.txt >&2 &
        fi
        $cmd 1>>rsh_stdout.txt 2>>rsh_stderr.txt
        rshRetval=$?
        if [ "$VERBOSE" == "v" ]; then 
            kill $! 1>/dev/null 2>/dev/null
        fi
        grep "Stale NFS file handle" rsh_stderr.txt 1>/dev/null 2>/dev/null
        if [ $? -ne 0 ] ; then   # if text not found, break
            break
        fi
    done
    if [ -s rsh_stdout.txt ] ; then
        writeLogOnly "----------- BEGIN TARGET STDOUT ------------"
        cat rsh_stdout.txt >>test.log 
        # if [ "$VERBOSE" == "v" ]; then cat rsh_stdout.txt >&2 ; fi
        writeLogOnly "----------- END TARGET STDOUT   ------------"
    fi
    if [ -s rsh_stderr.txt ] ; then
        writeLogOnly "----------- BEGIN TARGET STDERR ------------"
        cat rsh_stderr.txt >>test.log 
        # if [ "$VERBOSE" == "v" ]; then cat rsh_stderr.txt >&2 ; fi
        writeLogOnly "----------- END TARGET STDERR   ------------"
    fi
    cat rsh_stdout.txt rsh_stderr.txt > $rshOutFile
    rm -f rsh_stdout.txt rsh_stderr.txt
    return $rshRetval
}


E_OK=0
E_CONNECTION=1
E_TESTTIMEDOUT=2
E_FILENOTEXIST=3
E_TESTEXERETURNEDNONZERO=4
E_DIFF=5
E_REFERENCESTDOUT=6

filteredTestStdoutFile=test.stdout_filtered.txt

function runTest() {

    writeLog
    writeLog
    writeLog
    writeLog "testrunner> -------- STARTING TEST EXECUTION SEQUENCE --------"
    
    if [ $noPing == "false" ] ; then
        writeLog
        writeLog "testrunner> pinging the board to see if it's alive..."
        runRsh "echo \"Wassup\""
        if [ $rshRetval -ne 0 ] ; then return $E_CONNECTION ; fi
    fi
    
    # test setup
    if [ $noLoadModules == "false" ] ; then
        writeLog
        writeLog "testrunner> loading kernel modules..."
        runRsh "/home/test/setup/loadmodules.sh" # todo...
        if [ $rshRetval -ne 0 ] ; then return $E_CONNECTION ; fi
    fi
        
    writeLog
    writeLog "testrunner> cleaning up test target directory..."
    runRsh "rm -rf $targetTestDir/run ; mkdir -m 0777 -p $targetTestDir/run"
    if [ $rshRetval -ne 0 ] ; then return $E_CONNECTION ; fi
    
    writeLog
    writeLog "testrunner> copying test files (exe and auxiliary files)..."
    for file in $toTargetFiles ; do
        if [ ${file:0:1} != "/" ] ; then
            file=$pathToPackageBaseDir/$file
        fi
        if [ ! -f "$file" ] ; then
            writeErr "testrunner> Error: host file '$file' does not exist."
            return $E_NOFILE
        fi 
        if [ -z $targetNfsTestDir ] ; then
            runCmd rcp $file $targetTestAccount@$targetName:$targetTestDir/run
            if [ $cmdRetval -ne 0 ] ; then return $E_CONNECTION ; fi
        else 
            runCmd rcp $file $targetNfsTestDir/run
            if [ $cmdRetval -ne 0 ] ; then return $E_CONNECTION ; fi
        fi
    done
    
    # test exec    
    writeLog
    writeLog "testrunner> running test..."
    retvalKeyword=rsh:PROG_RETVAL
    runRsh "cd $targetTestDir/run ; ./$targetExeName $targetExeArgs ; echo $retvalKeyword=\$?"
    if [ $rshRetval -eq $E_TIMEOUT ] ; then return $E_TESTTIMEDOUT ; fi
    if [ $rshRetval -ne 0 ] ; then return $E_CONNECTION ; fi
    
    # preserve tests standard output (and error, they are fused in one file)
    rawTestStdoutFile="test.stdout_raw.txt"
    cp $rshOutFile $rawTestStdoutFile
    
    # grep the output for rsh:PROG_RETVAL=0 (success); if not found, retval = !0
    grep $retvalKeyword=0 $rawTestStdoutFile >/dev/null
    testRetval=$?  # exit code from grep
    writeLog "testrunner> target app exited with return value $testRetval"

    # test teardown
    if [ $noLoadModules == "false" ] ; then
        writeLog
        writeLog "testrunner> unloading kernel modules..."
        runRsh "/home/test/setup/unloadmodules.sh" # todo...
    fi
        
    # return immediately if test returned non-zero
    if [ $testRetval -ne 0 ] ; then return $E_TESTEXERETURNEDNONZERO ; fi

    # filter the output (in $rawTestStdoutFile)
    writeLog
    writeLog "testrunner> filtering returned stdout to file $filteredTestStdoutFile..."
    # remove retvalKeyword line -- that's ours, rest is up to user
    grep -v $retvalKeyword < $rawTestStdoutFile > $filteredTestStdoutFile
    # apply sed filters, if any
    for filt in $sedFilters ; do
        writeLog "            applying sed  filter with sed  -e '$filt'"
        sed -e "$filt" < $filteredTestStdoutFile > trtmp
        mv trtmp $filteredTestStdoutFile
    done    
    # apply grep -v filters, if any
    for filt in $grepFilters ; do
        writeLog "            applying grep filter with grep -v '$filt'"
        grep -v "$filt" < $filteredTestStdoutFile > trtmp
        mv trtmp $filteredTestStdoutFile
    done    
    
    # check if there's anything to copy back
    if [ "$fromTargetFiles" != "" ] ; then
        writeLog
        writeLog "testrunner> copying target-generated files back to the host..."
        for file in $fromTargetFiles ; do
            if [ -z $targetNfsTestDir ] ; then
                runCmd rcp $targetTestAccount@$targetName:$targetTestDir/run/$file .
                if [ $cmdRetval -ne 0 ] ; then return $E_CONNECTION ; fi
            else
                runCmd rcp $targetNfsTestDir/run/$file .
                if [ $cmdRetval -ne 0 ] ; then return $E_CONNECTION ; fi
            fi
        done
    fi
    
    
    # check if there's anything to be copied locally, for the purpose of diff
    if [ "$copyLocalFiles" != "" ] ; then
        writeLog
        writeLog "testrunner> copying local files to host test dir for diffing..."
        for file in $copyLocalFiles ; do
            if [ ${file:0:1} != "/" ] ; then
                file=$pathToPackageBaseDir/$file
            fi
            runCmd cp $file .
        done
    fi
    
        
    # now check if there are diffs to be done
    if [ "$diffFiles" != "" ] ; then
        writeLog
        writeLog "testrunner> running diff against generated files..."
        for filePair in $diffFiles ; do
            runCmd diff ${filePair/:/ }
            if [ $cmdRetval -ne 0 ] ; then return $E_DIFF ; fi 
        done
    fi

    # and check if there's a reference stdoutput to be compared against
    if [ "$referenceStdout" != "" ] ; then
        writeLog
        writeLog "testrunner> diffing filtered output with reference '$referenceStdout'..."
        srcFile=$referenceStdout 
        if [ ${srcFile:0:1} != "/" ] ; then
            srcFile=$pathToPackageBaseDir/$srcFile
        fi
        runCmd diff $srcFile $filteredTestStdoutFile
        if [ $cmdRetval -ne 0 ] ; then return $E_REFERENCESTDOUT ; fi 
    fi
    
    writeLog
    writeLog "testrunner> Test [$testName] execution ends at `date`" 
    
    # clean up the host test dir
    rm -f $cmdOutFile $rshOutFile
    
    return $E_OK
}

while [ 1 -eq 1 ] ; do

    runTest
    retval=$?
    if [ $retval -eq $E_OK ] ; then 
        # if a reference stdout file is not given,
        if [ "$referenceStdout" == "" ] ; then
            # output this for XDC or whoever
            writeLog "testrunner> outputing file $filteredTestStdoutFile to stdout:"
            cat $filteredTestStdoutFile
        else
            writeErr "testrunner> Test [$testName] PASSED."
        fi            
        exit 0 
    fi
    
    msg=
    if   [ $retval -eq $E_CONNECTION ] ; then 
        msg="Connection to target failed/lost/not permitted."
    elif [ $retval -eq $E_TESTTIMEDOUT ] ; then
        msg="Test application timed out."
    elif [ $retval -eq $E_FILENOTEXIST ] ; then
        msg="Input file(s) missing."
    elif [ $retval -eq $E_TESTEXERETURNEDNONZERO ] ; then
        msg="Test application returned nonzero."
    elif [ $retval -eq $E_DIFF ] ; then
        msg="Diff of input and generated files failed." 
    elif [ $retval -eq $E_REFERENCESTDOUT ] ; then
        msg="Diff of reference stdout and target stdout failed." 
    else
        msg="Unknown."
    fi
    if [ "$VERBOSE" == "v" ]; then writeErr ; fi
    writeErr "testrunner> Test [$testName] FAILED. Reason: $msg"

    # decide whether to go interactive about the failure or not
    if [ $noPrompting == "true" ] ; then 
        exit $retval
    fi
    if [ $extraPrompting == "false" ] ; then
        if [ $retval -ne $E_CONNECTION ] ; then
            exit $retval
        fi            
    fi
        
    while [ 1 -eq 1 ] ; do
        writeTerm
        writeTerm "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
        writeTerm "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
        writeTerm "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
        writeTerm "testrunner> USER INPUT REQUIRED: press action letter, then enter:    "
        writeTerm "testRunner> (a)bort, (r)etry, (i)gnore, show (l)og?"
        action=
        read action
        if [ $action == "a" ] ; then
            writeErr "testrunner> Test FAILED."
            exit 1
        elif [ $action == "r" ] ; then
            writeErr 
            writeErr "testrunner> rerunning test..."
            continue 2 
        elif [ $action == "i" ] ; then 
            writeErr "testrunner> Ignoring test failure."
            exit 0
        elif [ $action == "l" ] ; then 
            echo >&2
            echo "====================== BEGIN LOG =======================" >&2
            cat test.log >&2
            echo "====================== END LOG =======================" >&2
            echo >&2
        else
            writeTerm "testrunner> INVALID INPUT."        
        fi
    done
    
done
    
#
#  @(#) ti.platforms.evmDM6446; 1, 0, 0, 1,262; 2-23-2010 16:52:14; /db/ztree/library/trees/platform/platform-k32x/src/
#

