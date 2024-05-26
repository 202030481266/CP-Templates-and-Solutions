import json


def write_cpp_testcase(content):
    with open('./testcase_cpp.txt', 'w', encoding='utf-8') as writer:
        for q in content:
            # print(q, type(q))
            writer.write(' '.join(map(str, q)))
            writer.write('\n')
def test():
    with open('./testcase.txt', 'r', encoding='utf-8') as f:
        lines = f.readlines()
        for line in lines:
            content = json.loads(line)
            write_cpp_testcase(content) 
            
test()