valgrind --tool=massif --massif-out-file="usoRAM.out" ./corrector.o && massif-visualizer usoRAM.out
