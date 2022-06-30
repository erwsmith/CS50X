# example of binary search
# order of log_2(n)


def bisect(arr:list, x) -> int:
    
    # set initial indices of lowest and highest included elements to be searched
    lo = 0
    hi = len(arr)

    while lo < hi:
        mid = (lo + hi) // 2
        if arr[mid] < x:
            lo = mid + 1
        else:
            hi = mid
    return lo


def main():

    arr = [2, 3, 3, 4, 6, 7, 7, 8, 9]
    num = 5
    
    return arr[bisect(arr, num)] == num


if __name__ == '__main__':
    print(main())

    