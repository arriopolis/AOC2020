print(max(int(l.replace('F','0').replace('B','1').replace('L','0').replace('R','1'),2)for l in open('input.txt').readlines()))
