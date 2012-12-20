""" A tool to guess keys for vignere ciphers

    The ciphertext should only contain english alphabets
"""

import sys
import re

ALPHABET='ABCDEFGHIJKLMNOPQRSTUVWXYZ'

# Normalized english letter frequencies from wikipedia
FREQUENCIES=[0.6429696110848685, 0.11746181703668714, 0.2190206266729649, 0.33482916076208474, 1.0, 0.2460247349823322, 0.22250441696113077, 0.6729240282685514, 0.769213780918728, 0.01689487632508834, 0.08524734982332156, 0.44445671378091883, 0.26568021201413433, 0.7452517667844524, 0.8289531802120141, 0.21300795053003535, 0.01049028268551237, 0.6611086572438163, 0.6986528268551238, 1.0, 1.0, 0.41440677966101697, 1.0, 0.07598784194528875, 1.0, 0.074]

def normalize(freqs):
    m = float(max(freqs))
    return map(lambda x: x / m, freqs)

def score(freqs, shift):
    s = 0
    l = len(freqs)
    for i in range(l):
        s += (freqs[(i+shift) % l] - FREQUENCIES[i])**2
    return s

def best_shift(freqs):
    freqs = normalize(freqs)
    best_score = score(freqs, 0)
    best_i = 0
    for i in range(1, 26):
        s = score(freqs, i)
        if s < best_score:
            best_score = s
            best_i = i
    return best_i

def factorize(n):
    factors = []
    for i in range(2, n+1):
        if n % i == 0:
            factors.append(i)
    return factors

def find_repetitions(ctxt, length=2):
    repetitions = {}
    for i in range(len(ctxt)-length+1):
        pattern = ctxt[i:i+length]
        if pattern not in repetitions:
            repetitions[pattern] = len(re.findall(pattern, ctxt))
    return repetitions

def frequencies(ctxt, klength):
    f = []
    for start in range(klength):
        fi = {}
        for i in range(start, len(ctxt), klength):
            fi[ctxt[i]] = fi.get(ctxt[i], 0) + 1
        f.append(fi)
    return f

def guess_key(ctxt, freqs):
    key = ''
    for i in range(len(freqs)):
        f = [freqs[i].get(a,0) for a in ALPHABET]
        key += ALPHABET[best_shift(f)]
    return key

def decode(ctxt, key):
    txt = ''
    kl = len(key)
    for i in range(len(ctxt)):
        txt += ALPHABET[ALPHABET.index(ctxt[i]) - ALPHABET.index(key[i % kl])]
    return txt

def crack(ctxt, max_len=20):
    key_lengths = set()
    print 'Possible keys:'
    for length in range(1, max_len+1):
        r = find_repetitions(ctxt, length)
        rs = sorted(r.iteritems(), key=lambda y: y[1], reverse=True)

        diffs = set()
        for items in rs:
            if items[1] > 1:
                pat = re.compile(items[0])
                matches = list(re.finditer(pat, ctxt))
                for i in range(len(matches)-1):
                    diffs.add(matches[i+1].start() - matches[i].start())

        factors = []
        for d in diffs:
            if factors:
                factors = factors.intersection(factorize(d))
            else:
                factors = set(factorize(d))

        key_lengths = key_lengths.union(factors)

    for key_length in key_lengths:
        if key_length < max_len:
            print key_length
            freqs = frequencies(ctxt, key_length)
            key = guess_key(ctxt, freqs)
            print key
            txt = decode(ctxt, key)
            print txt
            print '---'

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print '\tUsage: {0} <file containing ciphertext> <max key length>'.format(sys.argv[0])
        sys.exit(1)

    ctxt = ''
    for line in open(sys.argv[1]):
        ctxt += line.replace(' ', '').replace('\r\n', '').upper()

    if len(sys.argv) > 2:
        crack(ctxt, int(sys.argv[2]))
    else:
        crack(ctxt)
