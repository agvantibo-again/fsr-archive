from yaml import load, dump
from subprocess import Popen, PIPE, STDOUT

##### ATEST - agvantibo's stupid little test runner #####

'''
- binary: <path>
  tests:
    - name: my test
      output: 4
      input: "2 2"
    - name: long input test
      output: 16
      input: | # multiline test cases as an indented block after |
        2 2
        2 2
    - name: another test
    ...

- binary: <another-path>
  ...
''' # YAML format. Key order in block does not matter.

tests_path = "./tests.yml"

# native import boilerplate
try:
    from yaml import CLoader as Loader, CDumper as Dumper
except ImportError:
    from yaml import Loader, Dumper

with open(tests_path) as tests_file:
    tests = load(tests_file, Loader=Loader)

# print(dump(tests, Dumper=Dumper))
for target in tests:
    max_len = max(map(lambda test: len(test['name']), target['tests'])) + 2
    for test in target['tests']:
        p = Popen(target['binary'], stdout=PIPE, stdin=PIPE, text=True)
        print(f"{target['binary']} running test \"{test['name']}\"...", end='')
        print(' ' * (max_len - len(test['name'])), end='')
        output = p.communicate(input=test['input'])[0].strip()
        if output == (test['output'].strip()):
            print("✅ OK")
        else:
            print("❌ Fail")
            print("Test case:")
            print(test['input'])
            print(f"Expected output: \"{test['output']}\"; got \"{output}\"")
