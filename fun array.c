
int findInMountainArray(int target, MountainArray* mountainArr) {
    int len = length(mountainArr), l = 0, r = len - 1;
    
    while (l < r){
        int mid = (l + r) >> 1;
        if (get(mountainArr, mid) < get(mountainArr, mid + 1))
            l = mid + 1;
        else
            r = mid;
    }
    
    int peak = l;
	
    l = 0, r = peak + 1;
    while (l < r){
        int mid = (l + r) >> 1;
        int num = get(mountainArr, mid);
        if (num > target)
            r = mid;
        else if (num < target)
            l = mid + 1;
        else
            return mid;
    }
    
    l = peak, r = len;
    while (l < r){
        int mid = (l + r) >> 1;
        int num = get(mountainArr, mid);
        if (num > target)
            l = mid + 1;
        else if (num < target)
            r = mid;
        else
            return mid;
    }
    return -1;
}