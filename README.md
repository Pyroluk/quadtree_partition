# Inital results

    qtpart -t 100 -i ../data/LatLong.psv -n 4
    Summary
    Total Points:      16740336
    Training Set Size: 100
    part[ 0] ->    4338267
    part[ 1] ->    3949577
    part[ 2] ->    4719648
    part[ 3] ->    3732844
    size:   4
    min:    3.73284e+06
    max:    4.71965e+06
    mean:   4.18508e+06
    stddev: 377229
    
    Estimated speedup:       3.54695
    Estimated time fraction: 0.281933
    qtpart -t 1000 -i ../data/LatLong.psv -n 4
    Summary
    Total Points:      16740336
    Training Set Size: 1000
    part[ 0] ->    4142481
    part[ 1] ->    4240222
    part[ 2] ->    4116276
    part[ 3] ->    4241357
    size:   4
    min:    4.11628e+06
    max:    4.24136e+06
    mean:   4.18508e+06
    stddev: 56472.1
    
    Estimated speedup:       3.94693
    Estimated time fraction: 0.253362
    qtpart -t 10000 -i ../data/LatLong.psv -n 4
    Summary
    Total Points:      16740336
    Training Set Size: 10000
    part[ 0] ->    4345246
    part[ 1] ->    4075261
    part[ 2] ->    4253026
    part[ 3] ->    4066803
    size:   4
    min:    4.0668e+06
    max:    4.34525e+06
    mean:   4.18508e+06
    stddev: 118659
    
    Estimated speedup:       3.85256
    Estimated time fraction: 0.259567
    qtpart -t 100000 -i ../data/LatLong.psv -n 4
    Summary
    Total Points:      16740336
    Training Set Size: 100000
    part[ 0] ->    4236067
    part[ 1] ->    4146732
    part[ 2] ->    4180227
    part[ 3] ->    4177310
    size:   4
    min:    4.14673e+06
    max:    4.23607e+06
    mean:   4.18508e+06
    stddev: 32226.4
    
    Estimated speedup:       3.95186
    Estimated time fraction: 0.253046
    ➜  experiments git:(master) ✗ make all
    qtpart -t 100 -i ../data/LatLong.psv -n 10
    Summary
    Total Points:      16740336
    Training Set Size: 100
    part[ 0] ->    1390373
    part[ 1] ->    2314938
    part[ 2] ->    1642289
    part[ 3] ->    2090310
    part[ 4] ->    2357254
    part[ 5] ->    1364669
    part[ 6] ->    2101215
    part[ 7] ->    1588766
    part[ 8] ->     971321
    part[ 9] ->     919201
    size:   10
    min:    919201
    max:    2.35725e+06
    mean:   1.67403e+06
    stddev: 498131
    Estimated speedup:       7.10163
    Estimated time fraction: 0.140813


    $ qtpart -t 1000 -i ../data/LatLong.psv -n 10
    Summary
    Total Points:      16740336
    Training Set Size: 1000
    part[ 0] ->    1432929
    part[ 1] ->    1731831
    part[ 2] ->    1766304
    part[ 3] ->    1685301
    part[ 4] ->    1568156
    part[ 5] ->    1629051
    part[ 6] ->    1906070
    part[ 7] ->    1757416
    part[ 8] ->    1688823
    part[ 9] ->    1574455
    size:   10
    min:    1.43293e+06
    max:    1.90607e+06
    mean:   1.67403e+06
    stddev: 124207
    Estimated speedup:       8.78264
    Estimated time fraction: 0.113861

    $ qtpart -t 10000 -i ../data/LatLong.psv -n 10
    Summary
    Total Points:      16740336
    Training Set Size: 10000
    part[ 0] ->    1669275
    part[ 1] ->    1648795
    part[ 2] ->    1665401
    part[ 3] ->    1573657
    part[ 4] ->    1630900
    part[ 5] ->    1694234
    part[ 6] ->    1681007
    part[ 7] ->    1736347
    part[ 8] ->    1701169
    part[ 9] ->    1739551
    size:   10
    min:    1.57366e+06
    max:    1.73955e+06
    mean:   1.67403e+06
    stddev: 46945.3
    Estimated speedup:       9.62337
    Estimated time fraction: 0.103914

    $ qtpart -t 100000 -i ../data/LatLong.psv -n 10
    Summary
    Total Points:      16740336
    Training Set Size: 100000
    part[ 0] ->    1696496
    part[ 1] ->    1621574
    part[ 2] ->    1699927
    part[ 3] ->    1678996
    part[ 4] ->    1678101
    part[ 5] ->    1669967
    part[ 6] ->    1650713
    part[ 7] ->    1675157
    part[ 8] ->    1660867
    part[ 9] ->    1708538
    size:   10
    min:    1.62157e+06
    max:    1.70854e+06
    mean:   1.67403e+06
    stddev: 24277.1
    Estimated speedup:       9.79805
    Estimated time fraction: 0.102061
