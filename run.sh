#/bin/bash
bash subRun.sh "lds" 1 50 &
bash subRun.sh "lds" 51 100&
bash subRun.sh "dfs" 1 50 &
bash subRun.sh "dfs" 51 100 &
bash subRun.sh "bfs" 1 50 &
bash subRun.sh "bfs" 51 100 &

