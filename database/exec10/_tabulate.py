from tabulate import tabulate

header=['Query Number',
'Estimated Disk Accesses',
'Actual Disk Accesses',
'Actual Run Time',
'Estimated Disk Accesses',
'Actual Disk Accesses',
'Actual Run Time','Performance Improvement']

data=[
    ['1', '6437.98', '49.312', '56.280', '6437.98', '38.684', '46.593', ''],
    ['2', '6191.27', '36.152', '36.434', '2922.21', '5.142', '5.481', ''],
    ['3', '4279.33', '12.246', '12.289', '8.02', '0.051', '0.087', ''],
    ['4', '0.01', '0.058', '0.078', '0.01', '0.198', '0.226', ''],
    ['5', '4565.99', '15.398', '15.443', '8.02', '0.053', '0.209', ''],
    ['6', '4565.99', '17.157', '17.186', '8.02', '0.089', '0.128', ''],
    ['7', '5526.35', '22.920', '24.348', '5527.35', '36.621', '38.030', ''],
]

for d in data:
    d[-1]=str((1-float(d[6])/float(d[3]))*100)[:6] + '%'

print(tabulate(data, header, tablefmt='grid'))
