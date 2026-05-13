# 풀이 회고

## 핵심 아이디어

배열을 한 번 순회하면서, 현재 원소와 쌍을 이뤄 `target`이 되는 값(`complement`)을 해시 맵에서 즉시 조회한다. 핵심은 **"이미 본 원소"만 해시 맵에 저장**한다는 점인데, 덕분에 같은 원소를 두 번 사용하는 경우를 자연스럽게 방지한다. 조회와 삽입이 모두 평균 O(1)인 해시 맵의 특성을 활용해, 중첩 반복문 없이 O(n) 단일 패스로 문제를 해결한다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map) — `unordered_map<값, 인덱스>` 형태로 "값 → 인덱스" 역방향 조회에 사용

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 단 한 번 순회하며, 각 원소에서 해시 맵 조회·삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우(정답이 배열 끝에 있는 경우) 모든 원소를 해시 맵에 저장하므로 O(n)

## 개선된 코드

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 값 → 인덱스 역방향 조회를 위한 해시 맵
        unordered_map<int, int> indexByValue;

        for (int currentIdx = 0; currentIdx < (int)nums.size(); currentIdx++) {
            int currentVal = nums[currentIdx];

            // target을 만들기 위해 현재 값과 쌍이 되어야 하는 보완값 계산
            int complement = target - currentVal;

            // 보완값이 이미 해시 맵에 존재하면 정답 쌍을 찾은 것
            if (indexByValue.count(complement)) {
                return {indexByValue[complement], currentIdx};
            }

            // 아직 쌍을 못 찾았으므로, 현재 값과 인덱스를 해시 맵에 기록
            indexByValue[currentVal] = currentIdx;
        }

        // 문제 조건상 항상 정답이 존재하므로 이 줄에는 도달하지 않음
        return {};
    }
};
```

## 다른 접근

- **브루트 포스 (Brute Force)** — 이중 반복문으로 가능한 모든 쌍 `(i, j)`을 확인해 합이 `target`인 경우를 반환한다. 추가 공간이 전혀 필요 없다는 장점이 있지만, 시간 복잡도가 O(n²)으로 입력이 커질수록 급격히 느려진다.

- **정렬 + 투 포인터 (Two Pointers)** — 배열을 정렬한 뒤 양 끝 포인터를 좁혀가며 합을 확인한다. 시간 복잡도는 O(n log n)으로 해시 맵 풀이보다 느리고, 정렬로 인해 원본 인덱스가 뒤섞이므로 인덱스를 함께 저장하는 별도 처리가 필요하다. 단, 해시 충돌이 없어 최악의 경우 성능이 안정적이다.

## 비슷한 문제

- LeetCode 167번 — Two Sum II (Input Array Is Sorted)
- LeetCode 15번 — 3Sum
- LeetCode 560번 — Subarray Sum Equals K