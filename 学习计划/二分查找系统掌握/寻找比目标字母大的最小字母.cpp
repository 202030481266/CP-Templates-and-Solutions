class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int l = -1, r = letters.size() - 1;
        // (l, r]
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (letters[mid] > target) r = mid;
            else l = mid;
        }
        return letters[r] > target ? letters[r] : letters[0];
    }
};