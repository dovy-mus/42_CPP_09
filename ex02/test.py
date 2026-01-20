import subprocess
import random
import sys
import time
def run_test(nums, label="Test"):
    args = ["./PmergeMe"] + [str(x) for x in nums]
    
    try:
        start_time = time.time()
        result = subprocess.run(args, capture_output=True, text=True, timeout=60)
        duration = time.time() - start_time
        
        output = result.stdout
        
        if result.returncode != 0:
            print(f"FAILED ({label}): Return code {result.returncode}")
            print(result.stderr)
            return False
        # Extract "After:" line
        lines = output.split('\n')
        after_line = None
        for line in lines:
            if line.startswith("After:"):
                after_line = line
                break
        
        if not after_line:
            print(f"FAILED ({label}): No 'After:' line found")
            return False
            
        sorted_nums_str = after_line.replace("After: ", "").split()
        sorted_nums = [int(x) for x in sorted_nums_str]
        
        expected_sorted = sorted(nums)
        
        if len(sorted_nums) != len(nums):
             print(f"FAILED ({label}): Size mismatch. Expected {len(nums)}, got {len(sorted_nums)}")
             return False
        if sorted_nums != expected_sorted:
            print(f"FAILED ({label}): Content mismatch.")
            # Print first few mismatches
            for i in range(min(len(sorted_nums), len(expected_sorted))):
                if sorted_nums[i] != expected_sorted[i]:
                    print(f"Index {i}: Expected {expected_sorted[i]}, got {sorted_nums[i]}")
                    break
            return False
            
        if "Vector is sorted: Yes" not in output:
             print(f"FAILED ({label}): Vector reported as not sorted")
             return False
        if "List is sorted: Yes" not in output:
             print(f"FAILED ({label}): List reported as not sorted")
             return False
        print(f"PASSED ({label}) - Size: {len(nums)}, Real Time: {duration:.4f}s")
        return True
        
    except subprocess.TimeoutExpired:
        print(f"TIMEOUT ({label})")
        return False
    except Exception as e:
        print(f"ERROR ({label}): {e}")
        return False
def main():
    print("Running comprehensive tests...")
    
    if not run_test([1], "Single Element"): sys.exit(1)
    if not run_test([2, 1], "Two Elements"): sys.exit(1)
    if not run_test([1, 2, 3, 4, 5], "Already Sorted"): sys.exit(1)
    if not run_test([5, 4, 3, 2, 1], "Reverse Sorted"): sys.exit(1)
    
    if not run_test([4, 1, 4, 3], "Duplicates 1"): sys.exit(1)
    if not run_test([2, 2, 2, 2], "All Duplicates"): sys.exit(1)
    
    nums = [random.randint(1, 100) for _ in range(21)]
    if not run_test(nums, "Random 21"): sys.exit(1)
    
    nums = [random.randint(1, 1000) for _ in range(101)]
    if not run_test(nums, "Random 101"): sys.exit(1)
    
    nums = [random.randint(1, 100000) for _ in range(3000)]
    if not run_test(nums, "Random 3000"): sys.exit(1)
    
    nums = [random.randint(1, 100000) for _ in range(10000)]
    if not run_test(nums, "Random 10000"): sys.exit(1)
    print("\nAll comprehensive tests passed!")
if __name__ == "__main__":
    main()
