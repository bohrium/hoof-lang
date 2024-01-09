import sys

_, in_file, out_file, verbosity = sys.argv
assert verbosity in {'LOUD', 'QUIET'}
verbose = (verbosity=='LOUD')

with open(in_file) as f:
    lines = f.read().split('\n')

def process_line(ln):

    if ln.startswith('#'):
        if verbose: print('\033[34m' + ln)
        return ln
    elif ln.startswith('[[TIME]]'):
        if verbose: print('\033[33m' + ln)
        return ''
    else:
        return ln

if verbose: print('\033[36m')
with open(out_file, 'w') as f:
    f.write('\n'.join(process_line(ln) for ln in lines))
if verbose: print('\033[36m')
