
# Program to convert source datafile to required format

FILENAMES = {
    'mass': 'mass.txt',
    'power': 'power.txt',
    'pitch_angle': 'pitch_angle.txt'
}
for f in FILENAMES: FILENAMES[f] = 'datafiles/timetable/' + FILENAMES[f]

srcfile = open(r"datafiles\table_t_m_p_tet_123-0.txt", 'r')

t = []
mass = []
power = []
pitchAngle = []

for line in srcfile:
    vals = []
    for v in line.replace('\n', '').split(' '):
        if v: vals.append(v)
    t.append(vals[0])
    mass.append(vals[1])
    power.append(vals[2])
    pitchAngle.append(vals[3])

assert( len(t) == len(mass) == len(pitchAngle) == len(power) )

def writeFormatted(filename, time, vals):
    file = open(filename, 'w')
    file.write(str(len(time)) + '\n')
    file.writelines([f"{time[i]} {vals[i]}\n" for i in range(len(time))])

writeFormatted(FILENAMES['mass'], t, mass)
writeFormatted(FILENAMES['power'], t, power)
writeFormatted(FILENAMES['pitch_angle'], t, pitchAngle)