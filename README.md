# Inital results

    $ quadtree_partition git:(master) ✗ qtpart -n 4 -t 100 -i data/LatLong.psv
    Summary
    Total Points:      16740336
    Training Set Size: 100
    part[ 0] ->    3705311
    part[ 1] ->    4803095
    part[ 2] ->    4520964
    part[ 3] ->    3710966
    size:   4
    min:    3.70531e+06
    max:    4.8031e+06
    mean:   4.18508e+06
    stddev: 487269

    $ quadtree_partition git:(master) ✗ qtpart -n 4 -t 1000 -i data/LatLong.psv
    Summary
    Total Points:      16740336
    Training Set Size: 1000
    part[ 0] ->    4704177
    part[ 1] ->    4018025
    part[ 2] ->    4320241
    part[ 3] ->    3697893
    size:   4
    min:    3.69789e+06
    max:    4.70418e+06
    mean:   4.18508e+06
    stddev: 371816
    
    $ quadtree_partition git:(master) ✗ qtpart -n 4 -t 10000 -i data/LatLong.psv
    Summary
    Total Points:      16740336
    Training Set Size: 10000
    part[ 0] ->    4227300
    part[ 1] ->    4209215
    part[ 2] ->    4047348
    part[ 3] ->    4256473
    size:   4
    min:    4.04735e+06
    max:    4.25647e+06
    mean:   4.18508e+06
    stddev: 81289.7
    
    $ quadtree_partition git:(master) ✗ qtpart -n 4 -t 100000 -i data/LatLong.psv
    Summary
    Total Points:      16740336
    Training Set Size: 100000
    part[ 0] ->    4203162
    part[ 1] ->    4154432
    part[ 2] ->    4219860
    part[ 3] ->    4162882
    size:   4
    min:    4.15443e+06
    max:    4.21986e+06
    mean:   4.18508e+06
    stddev: 27242.7