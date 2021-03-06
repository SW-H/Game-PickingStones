# Game-PickingStones

## 게임규칙
▪ 1부터 n까지 숫자가 매겨진 n개의 돌로 시작한다.   
▪ Max 플레이어와 Min 플레이어가 번갈아 가면서 돌을 하나씩 가져간다.   
▪ 첫 번째 플레이어는 n/2보다 작은 숫자 중에서 홀수 돌을 선택해야만 한다.   
n이 7인 경우(n/2=3.5), 1 과 3   
n이 6인 경우(n/2=3), 1   
▪ 다음 플레이어는 마지막 제거된 돌의 배수(multiple) 또는 인수(factor)만 가져올 수 있다.(1은 모든 수의 인수)   
▪ 플레이어의 차례에 가지고 갈 돌이 없는 경우 패배한다.   
Max Player : 3 (7/3=3.5이므로 3.5보다 작은 홀수 1또는 3) Min Player : 6 (3의 배수)   
Max Player : 2 (6의 인수)   
Min Player : 4 (2의 배수)   
MaxPlayer:1 (1은모든수의인수)   
Min Player : 7   
Winner: Min Player (가져갈 돌이 남아 있지 않으므로 Max플레이어 패배)   
    
▪ 가져간 돌이 없으면, Max플레이어가 먼저 시작한다.   
▪ 프로그램은 평가 함수를 사용하여 현재 플레이어를 위한 최선의 돌을 선택한다.   
   
## 구현 내용   
▪ Eclipse(C, C++언어 사용)   
▪ Alpha-Beta pruning algorithm 구현   
▪ 입력   
   play <num_of_stones> <num_of_taken_stones> <list_of_taken_stones> 
    ▪ num_of_stones : 게임에 주어진 전체 돌의 개수
    ▪ num_of_taken_stones : 가져간 돌의 개수
    0이면 게임 시작이고 Max플레이어 차례 짝수이면 Max플레이어 차례
    홀수이면 Min플레이어 차례
▪ list_of_taken_stones : 가져간 돌의 리스트    
예) $ play 7 2 3 6
 두 개의 돌(3과 6)을 가지고 갔으므로 Max플레이어 차례

▪ 출력
▪ alpha-beta 알고리즘으로 계산한 최선의 돌   
▪ alpha-beta 알고리즘으로 계산한 값    
▪ 방문한 노드의 총 숫자   
▪ 노드의 최대 깊이(depth)   
예) Input:
$ play 7 3 1 4 2   

Output:
Best Move : 6
Calculated Value : 1.0 
Number of Visited Nodes : 3 
Max Depth : 2

▪ Evaluation
▪ 게임 종료 시, Max 플레이어 승리 : 1.0 
▪ 게임 종료 시, Min 플레이어 승리 : -1.0 
▪ 그밖에

- Max 플레이어 차례
1번 돌을 아직 가지고 가지 않은 경우 : 0반환
마지막에 1을 가지고 간 경우, 가지고 올 수 있는 숫자 세어서
홀수면 0.5, 짝수는 -0.5 반환
마지막에 소수를 가지고 간 경우, 소수의 배수를 계산하여 개수를 세어서
홀수면 0.7 짝수면 -0.7반환 마지막에 소수가 아닌 돌을 가지고 간 경우, 소수의 개수를 세어서
홀수면 0.6 짝수면 -0.6반환

- Min 플레이어 차례
1번 돌을 아직 가지고 가지 않은 경우 : 0반환    
마지막에 1을 가지고 간 경우, 가지고 올 수 있는 숫자 세어서    
     
홀수면 -0.5, 짝수는 0.5 반환   
마지막에 소수를 가지고 간 경우, 소수의 배수를 계산하여 개수를 세어서    
홀수면 -0.7 짝수면 0.7반환 마지막에 소수가 아닌 돌을 가지고 간 경우, 소수의 개수를 세어서   
홀수면 -0.6 짝수면 0.6반환     

▪ alpha 초기값 : -∞(negative infinity) beta 초기값 : ∞(positive_infinity)   

▪ 동일한값이계산된경우,작은숫자의돌을선택한다. 예) 2와 6의 평가 값이 같은 경우, 2를 선택한다    
