import os
import subprocess
import sys
import difflib
import logging

# -------------------- Configuration Section -------------------- #
# Define your C programs and their corresponding test case directories here.
# Format: "C_PROGRAM_PATH": "TEST_CASE_DIRECTORY"

mappings = {
    "CsTest2/CsTest2.c": "tc_CsTest2",
    # Add more mappings as needed, e.g.,
    # "AnotherProgram/AnotherProgram.c": "tc_hw2",
}
# -------------------- End of Configuration --------------------- #

def compile_c_program(source_file, output_executable):
    """
    Compiles the given C source file using gcc.
    Returns True if compilation succeeds, False otherwise.
    """
    compile_command = ['gcc', source_file, '-o', output_executable]
    try:
        subprocess.check_output(compile_command, stderr=subprocess.STDOUT)
        message = f"[+] Compilation succeeded for {source_file}."
        print(message)
        logging.info(message)
        return True
    except subprocess.CalledProcessError as e:
        message = f"[-] Compilation failed for {source_file}.\nError:\n{e.output.decode()}"
        print(message)
        logging.error(message)
        return False

def run_test(executable, input_file, expected_output_file):
    """
    Runs the executable with the given input file.
    Compares the output with the expected output.
    Returns (True, actual_output) if test passes, (False, actual_output) otherwise.
    """
    try:
        with open(input_file, 'r') as infile:
            result = subprocess.run(
                [f'./{executable}'],
                stdin=infile,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=5  # seconds
            )
        
        with open(expected_output_file, 'r') as exp_out:
            expected = exp_out.read().strip()
        
        actual = result.stdout.strip()
        
        # Normalize whitespace for comparison
        expected_normalized = ' '.join(expected.split())
        actual_normalized = ' '.join(actual.split())
        
        if actual_normalized == expected_normalized:
            return True, actual
        else:
            # Generate a unified diff for detailed comparison
            diff = difflib.unified_diff(
                expected.splitlines(),
                actual.splitlines(),
                fromfile='expected',
                tofile='actual',
                lineterm=''
            )
            return False, '\n'.join(diff)
    except subprocess.TimeoutExpired:
        return False, "Execution timed out."
    except Exception as e:
        return False, f"Error: {str(e)}"

def setup_logging():
    """
    Configures the logging settings.
    """
    logging.basicConfig(
        filename='test_results.log',
        filemode='w',
        level=logging.INFO,
        format='%(asctime)s - %(levelname)s - %(message)s'
    )

def main():
    setup_logging()
    print("Starting the C Programs Testing Script...\n")
    logging.info("=== Starting the C Programs Testing Script ===\n")
    
    for c_file, tc_dir in mappings.items():
        print(f"=== Testing {c_file} ===")
        logging.info(f"=== Testing {c_file} ===")
        
        # Check if C program file exists
        if not os.path.isfile(c_file):
            message = f"[-] C program file '{c_file}' does not exist."
            print(message)
            logging.error(message)
            continue
        
        # Check if test case directory exists
        if not os.path.isdir(tc_dir):
            message = f"[-] Test case directory '{tc_dir}' for program '{c_file}' not found."
            print(message)
            logging.error(message)
            continue
        
        # Compile the C program
        program_base = os.path.splitext(os.path.basename(c_file))[0]
        executable = f"{program_base}_exec"
        compiled = compile_c_program(c_file, executable)
        if not compiled:
            continue  # Skip testing if compilation failed
        
        print(f"[*] Using test cases from '{tc_dir}'.")
        logging.info(f"[*] Using test cases from '{tc_dir}'.")
        
        # Gather all .in test case files
        test_files = sorted([f for f in os.listdir(tc_dir) if f.endswith('.in')])
        
        if not test_files:
            message = f"[-] No input test case files found in '{tc_dir}'."
            print(message)
            logging.warning(message)
            os.remove(executable)  # Cleanup
            continue
        
        passed = 0
        failed = 0
        total = len(test_files)
        
        for test_in in test_files:
            test_base = os.path.splitext(test_in)[0]  # e.g., 'tc01'
            input_path = os.path.join(tc_dir, f"{test_base}.in")
            expected_output_path = os.path.join(tc_dir, f"{test_base}.out")
            
            # Check if expected output file exists
            if not os.path.isfile(expected_output_path):
                message = f"    [!] Missing expected output file for test case '{test_base}'. Skipping."
                print(message)
                logging.warning(message)
                continue
            
            # Run the test
            success, output = run_test(executable, input_path, expected_output_path)
            
            if success:
                message = f"    [PASS] {test_base}"
                print(message)
                logging.info(message)
                passed += 1
            else:
                message = f"    [FAIL] {test_base}\n          {output}"
                print(message)
                logging.error(message)
                failed += 1
        
        # Summary for the current program
        summary = f"    [SUMMARY] Passed: {passed}/{total}, Failed: {failed}/{total}\n"
        print(summary)
        logging.info(summary)
        
        # Cleanup the executable
        if os.path.exists(executable):
            os.remove(executable)
            cleanup_message = f"    [CLEANUP] Removed executable '{executable}'.\n"
            print(cleanup_message)
            logging.info(cleanup_message)
    
    print("Testing Completed. Check 'test_results.log' for detailed logs.")
    logging.info("=== Testing Completed ===")

if __name__ == "__main__":
    main()