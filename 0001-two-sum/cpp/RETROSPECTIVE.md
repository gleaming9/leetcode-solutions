# 풀이 회고

## 핵심 아이디어

배열을 왼쪽부터 순회하면서, 현재 원소와 짝을 이루어 `target`이 되는 "보완값(complement)"이 이미 앞에서 등장했는지를 해시 맵으로 O(1)에 조회한다. 찾으면 즉시 두 인덱스를 반환하고, 없으면 현재 원소를 해시 맵에 기록한 뒤 다음으로 넘어간다. 이처럼 "기록과 조회를 동시에" 수행하기 때문에, 같은 원소를 두 번 사용하는 오류 없이 단일 순회만으로 정답을 구할 수 있다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map, `unordered_map`): 값 → 인덱스 역방향 조회
- 단일 순회 (Single Pass): 배열을 한 번만 탐색

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번만 순회하며, 각 원소마다 해시 맵 조회/삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 해시 맵에 저장해야 하므로 O(n)

## 개선된 코드

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 값 → 인덱스 매핑을 저장하는 해시 맵
        unordered_map<int, int> indexByValue;

        for (int currentIdx = 0; currentIdx < nums.size(); currentIdx++) {
            // target을 만들기 위해 현재 값과 짝이 되어야 하는 보완값 계산
            int complement = target - nums[currentIdx];

            // 보완값이 이미 앞선 순회에서 등장했는지 확인
            if (indexByValue.count(complement)) {
                // 보완값의 인덱스와 현재 인덱스를 정답으로 반환
                return {indexByValue[complement], currentIdx};
            }

            // 현재 값을 해시 맵에 기록 (이후 원소의 보완값 조회에 활용)
            indexByValue[nums[currentIdx]] = currentIdx;
        }

        // 문제 조건상 항상 정답이 존재하므로 이 지점에 도달하지 않음
        return {};
    }
};
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
이중 반복문으로 모든 쌍 `(i, j)`를 검사해 합이 `target`인 경우를 찾는다. 추가 공간이 전혀 필요 없지만, 배열 길이가 커질수록 시간 비용이 급격히 증가한다. 입력 크기가 작거나 공간이 극도로 제한된 환경에서는 고려할 만하다.

**② 정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
배열을 값 기준으로 정렬한 뒤, 양 끝에서 포인터를 좁혀가며 합을 찾는다. 단, 정렬 후 원래 인덱스 정보가 사라지므로 `(값, 원본 인덱스)` 쌍을 별도로 보관해야 한다. 해시 맵 방식보다 시간 복잡도가 약간 높지만, 해시 충돌이 없고 메모리 접근 패턴이 연속적이라 실제 캐시 성능이 좋은 경우도 있다.

## 비슷한 문제

- **LeetCode 167** - Two Sum II (Input Array Is Sorted): 정렬된 배열에서의 Two Sum, 투 포인터 적용 연습
- **LeetCode 15** - 3Sum: 세 수의 합이 0이 되는 모든 조합 탐색, 중복 처리 난이도 상승
- **LeetCode 560** - Subarray Sum Equals K: 누적 합과 해시 맵을 결합한 응용 문제