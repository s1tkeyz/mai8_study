import sys
import random
import string

TEST_COUNT = 10
MD5_LENGTH = 32

def get_random_string():
    length = random.randint(10, 2048)
    random_list = [ random.choice(string.ascii_letters) for _ in range(length) ]
    return "".join(random_list)

def get_random_md5():
    random_list = [ random.choice("0123456789abcdef") for _ in range(MD5_LENGTH) ]
    return "".join(random_list)

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)

    test_dir = sys.argv[1]

    lines = [0]
    lines.extend([ 4 ** i for i in range(TEST_COUNT) ])

    for enum, test_count in enumerate(range(1, TEST_COUNT+1)):
        test = []
        answer = []

        line_count = lines[enum]
        for _ in range(line_count):
            key = get_random_md5()
            value = get_random_string()
            test.append((key, value))

        test_name = "{}/{:02d}".format(test_dir, test_count)
        with open(f'{test_name}.t', 'w') as ftest:
            for key, value in test:
                ftest.write(f'{key}\t{value}\n')

        answer = test
        for i in range(MD5_LENGTH):
            answer = sorted(answer, key=lambda x : int(x[0][MD5_LENGTH - 1 - i], base=16))

        with open(f'{test_name}.a', 'w') as ftest:
            for key, value in answer:
                ftest.write(f'{key}\t{value}\n')
main()