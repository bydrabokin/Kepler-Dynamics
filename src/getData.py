import requests
from datetime import datetime, timezone, timedelta
import math

def name(planet, response):
    nameStart = response.text.find("Revised:")
    nameEnd = response.text.find(f"{planet}") +1
    name = response.text[nameStart:nameEnd]
    name = name[name.find("   "):].strip()
    name = name[:name.find("/")].strip()
    return name

def centerBody(planet, response):
    centerBodyStart = response.text.find("Revised:")
    centerBodyEnd = response.text.find(f"{planet}") +1
    centerBody = response.text[centerBodyStart:centerBodyEnd]
    centerBody = centerBody[centerBody.find("/ ")+2:].strip()
    centerBody = centerBody[:centerBody.find(")")].strip()
    if response.text[centerBodyStart:centerBodyEnd].count("/") == 0:
        centerBody = "Sun"
    if planet == "10":
        centerBody = "N/A"
    if centerBody.count("(") > 0:
        centerBody = centerBody[1:]

    return centerBody

def mass(response):
    massStart = response.text.find("Mass") + 4
    mass = response.text[massStart:].strip()

    massExponentStart = mass.find("^")+1
    massExponent = mass[massExponentStart:massExponentStart+2]

    mass = mass[mass.find("=")+2:].strip()

    if mass.count("+") > 0: 
        mass = mass[:mass.find("+")]
        
    mass = mass[:mass.find(" ")]
    if mass.count("\n") > 0:
        mass = mass[:-1]

    if mass.count("~") > 0:
        mass = mass[1:]

    mass = mass + "e" + massExponent

    if response.text.count("Mass") == 0:
        mass = "N/A"

    try:
        float(mass)
    except ValueError:
        mass = "N/A" 
    return mass

def radius(response):
    radius = response.text.lower()
    radiusStart = radius.find("radius") 
    radius = response.text[radiusStart:]
    radius = radius[radius.find("=")+2:]
    radiusEnd = radius.find("  ")
    radius = radius[:radiusEnd].strip()

    if radius.count("+") > 0: 
        radius = radius[:radius.find("+")]
    if radius.count("D") > 0: 
        radius = radius[:radius.find("D")]
    if radius.count("x") > 0:
        radiusSplitted = radius.split('x')
        radius1 = float(radiusSplitted[0].strip())
        radius2 = float(radiusSplitted[1])
        radius3 = float(radiusSplitted[2])
        meanRadius = math.cbrt(radius1*radius2*radius3)
        radius = f"{meanRadius}"
    if response.text.lower().count("radius") == 0:
        radius = "N/A"

    return radius

def posAndVel(response):
    Xstart = response.text.find("X =") +3
    X=response.text[Xstart:Xstart+22].strip().lower()
    Ystart = response.text.find("Y =") + 3
    Y=response.text[Ystart:Ystart+22].strip().lower()
    Zstart = response.text.find("Z =") + 3
    Z=response.text[Zstart:Zstart+22].strip().lower()
    VXstart = response.text.find("VX=") + 3
    VX=response.text[VXstart:VXstart+22].strip().lower()
    VYstart = response.text.find("VY=") + 3
    VY=response.text[VYstart:VYstart+22].strip().lower()
    VZstart = response.text.find("VZ=") + 3
    VZ=response.text[VZstart:VZstart+22].strip().lower()

    return X, Y, Z, VX, VY, VZ

def axialTilt(response):
    tiltStart = response.text.find("Obliquity to orbit")
    tilt = response.text[tiltStart:]
    tiltStart = tilt.find("=")+1
    tilt = tilt[tiltStart:]

    i = 0
    while i < len(tilt) and not tilt[i].isalpha():
        i += 1

    tiltEnd = i
    tilt = tilt[:tiltEnd].strip()

    if response.text.count("Obliquity to orbit") == 0:
        tilt = "N/A"

    return tilt

def bondAlbedo(response):
    text = response.text.lower()
    albedoStart = text.find("geometric albedo")
    albedo = response.text[albedoStart:]
    albedoStart = albedo.find("=")+1
    albedo = albedo[albedoStart:]

    i = 0
    while i < len(albedo) and not albedo[i].isalpha():
        i += 1

    albedoEnd = i
    albedo = albedo[:albedoEnd].strip()

    text = response.text.lower()
    if text.count("geometric albedo") == 0:
        albedo = "N/A"

    return albedo

def meanSolarDay(response):
    pass
now = datetime.now(timezone.utc)


url = "https://ssd.jpl.nasa.gov/api/horizons.api"
epheim = "VECTORS"
format = "text"
planet = "-31"

params = {
    "format":format,

    #Planet
    "COMMAND": f"{planet}",

    #Center
    "CENTER": "'500@10'",

    # #Vectors
    "VEC_TABLE": "'2'",
    "EPHEM_TYPE":epheim,

    #time
    "START_TIME": f"'{now.strftime('%Y-%m-%d %H:%M')}'",
    "STOP_TIME": f"'{(now + timedelta(minutes=1)).strftime('%Y-%m-%d %H:%M')}'",
    "STEP_SIZE": "'1 m'",
}

response = requests.post(url, data=params)
print(response.text)

print("**Data Extracted Form NASA's JPL/Horizons' API**\n")
print(f"Date: {now}")

#code 
print("Code: " + planet)

#name
print("Name: " + name(planet, response))

#Center body name
print("Center Body: " + centerBody(planet, response))

#mass
print("Mass: " + mass(response))

#radius
print("Raius: " + radius(response))

#tilt
print("Axial Tilt: " + axialTilt(response))

#geometrical albedo
print("Bond albedo: " + bondAlbedo(response))

#postion and velocity
X, Y, Z, VX, VY, VZ = posAndVel(response)
print(f"X: {X}\nY: {Y}\nZ: {Z}\nVX: {VX}\nVY: {VY}\nVZ: {VZ}\n")



