import requests
from datetime import datetime, timezone, timedelta
import math

def name(planet, response):
    if planet[-1] == ";":
        nameStart = response.text.find("JPL/HORIZONS")
        name = response.text[nameStart:]
        nameStart = name.find(f"{planet[:-1]}") + len(planet[:-1])
        name = name[nameStart:]
        nameEnd = name.find("(")
        name = name[:nameEnd].strip()

    else:
        nameStart = response.text.find("Revised:")
        nameEnd = response.text.find(f"{planet}") + 1 
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

def radius(planet, response):
    radius = response.text.lower()
    if planet == "999":
        radiusStart = radius.find("mean radius") 
    else:
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
        radius2 = float(radiusSplitted[1].strip())
        radius3 = float(radiusSplitted[2].strip())
        meanRadius = math.cbrt(radius1*radius2*radius3)
        radius = f"{meanRadius}"
    if response.text.lower().count("radius") == 0:
        return "N/A"
    
    radius = f"{float(radius)*1000}"

    return radius

def posAndVel(response):
    
    Xstart = response.text.find("X =") +3
    X=response.text[Xstart:Xstart+22].strip().lower()
    X = f"{float(X)*1000}"    
    Ystart = response.text.find("Y =") + 3
    Y=response.text[Ystart:Ystart+22].strip().lower()
    Y = f"{float(Y)*1000}"    
    Zstart = response.text.find("Z =") + 3
    Z=response.text[Zstart:Zstart+22].strip().lower()
    Z = f"{float(Z)*1000}"    
    VXstart = response.text.find("VX=") + 3
    VX=response.text[VXstart:VXstart+22].strip().lower()
    VX = f"{float(VX)*1000}"    
    VYstart = response.text.find("VY=") + 3
    VY=response.text[VYstart:VYstart+22].strip().lower()
    VY = f"{float(VY)*1000}"    
    VZstart = response.text.find("VZ=") + 3
    VZ=response.text[VZstart:VZstart+22].strip().lower()
    VZ = f"{float(VZ)*1000}"

    
    return X, Y, Z, VX, VY, VZ

def axialTilt(response):
    tiltStart = response.text.find("Obliquity to orbit")
    tilt = response.text[tiltStart:]
    tiltStart = tilt.find("=")+1
    tilt = tilt[tiltStart:]

    i = 0
    while i < len(tilt) and not (tilt[i].isalpha() or tilt[i] == "'"):
        i += 1

    tiltEnd = i
    tilt = tilt[:tiltEnd].strip()

    if response.text.count("Obliquity to orbit") == 0:
        tilt = "N/A"

    return tilt

def bondAlbedo(response):
    text = response.text.lower()
    albedoStart = text.find("geometric albedo")

    if (text.count("geometric albedo") == 0):
        return "N/A"
    
    albedo = response.text[albedoStart:]
    albedoStart = albedo.find("=")+1
    albedo = albedo[albedoStart:]

    i = 0
    while i < len(albedo) and not (albedo[i].isalpha() or albedo[i] == "(" or albedo[i] == "+"):
        i += 1

    albedoEnd = i
    albedo = albedo[:albedoEnd].strip()

    text = response.text.lower()
    if text.count("geometric albedo") == 0:
        albedo = "N/A"

    if not albedo:

        return "N/A"
    
    return albedo

def meanSolarDay(response):
    factor = 1
    solarStart = response.text.find("Mean solar day")

    if (response.text.count("Mean solar day") == 0):
        return "N/A"
    
    solar = response.text[solarStart:solarStart+100]

    if solar.count("hrs") > 0 or solar.count(" h ") > 0:
        factor = 3600

    solarStart = solar.find("=") + 1
    solar = solar[solarStart:]

    i = 0
    while i < len(solar) and not (solar[i].isalpha() or solar[i] == "("):
        i += 1

    if solar[i] == "d" and factor == 1:
        factor = 60*60*24


    solarEnd = i
    solar = solar[:solarEnd].strip()

    if solar[0] == "~":
        solar = solar[1:]


    solar = f"{float(solar)*factor}"

    return solar

def temp(response):

    text = response.text.lower()
    if (text.count("temp") == 0):
            return "N/A"

    tempStart = text.find("temp")
    temp = response.text[tempStart:]
    tempStart = temp.find("=")+1
    temp = temp[tempStart:]
    i = 0
    while i < len(temp) and not (temp[i].isalpha() or temp[i] == "+" or temp[i] == "("):
        i += 1

    tempEnd = i
    temp = temp[:tempEnd].strip()

    return temp

def pressure(response):

    text = response.text.lower()
    if (text.count("pressure") == 0):
            return "N/A"

    pressureStart = text.find("pressure")
    pressure = response.text[pressureStart:]
    pressureStart = pressure.find("=")+1
    pressure = pressure[pressureStart:]
    i = 0
    while i < len(pressure) and not (pressure[i].isalpha() or pressure[i] == "+"):
        i += 1

    pressureEnd = i
    pressure = pressure[:pressureEnd].strip()

    if (pressure.count("<") > 0):
        pressure = pressure[pressure.find("<")+1:].strip()

    pressure = f"{float(pressure)*100000}"
    
    return pressure

now = datetime.now(timezone.utc)

with open("data.txt", "w") as f:
    f.write(f"{now}")


url = "https://ssd.jpl.nasa.gov/api/horizons.api"
epheim = "VECTORS"
format = "text"


listPlanets = [
    # Planets
    "10",  # Sun (definetly not a planet)
    "199", # Mercury
    "299", # Venus
    "399", # Earth
    "499", # Mars
    "599", # Jupiter
    "699", # Saturn
    "799", # Uranus
    "899", # Neptune
    "999"  # Pluto, Note: I know is technically not a planet, it is for me
]

dwarfPlanets = [
    "1;", # Ceres
    "2;", # Pallas
    "3;", # Juno
    "4;", # Vesta
    "136199;", # Eris
    "136108;", # Haumea
    "136472;"  # Makemake
]

listMoons = [

    "301", # Moon
    "401", "402", # Phobos, Deimos
    "501", "502", "503", "504", # Io, Europa, Ganymede, Callisto
    "601", "602", "603", "604", "605", "606", "607", "608", "609", # Mimas, Enceladus, Tethys, Dione, Rhea, Titan, Hyperion, Iapetus, Phoebe
    "701", "702", "703", "704", "705", # Ariel, Umbriel, Titania, Oberon, Miranda, 
    "801", "802", # Triton, Nereid
    "901", "902", "903", "904", "905" # Charon, Nix, Hydra, Kerberos, Styx
]

listSpacecraft = [
    "-31", # Voyager 1 Spacecraft (interplanetary)
    "-32", # Voyager 2 Spacecraft (interplanetary)
    "-98", # New Horizons Spacecraft
    "-61", # Juno Spacecraft
    "-23", # Pioneer 10 Spacecraft (interplanetary)
    "-24", # Pioneer 11 Spacecraft
    "-96", # Parker Solar Probe
    "-64", # OSIRIS-REx
    "-203" # Dawn Spacecraft (interplanetary)

]



params = {
    "format":format,

    #Planet
    "COMMAND": "0",

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

print(f"\nDate: {now}")

print("\nFetching planet data from NASA...")

with open("data.txt", "a") as f:
    f.write("\n\nPLANETS")

for planetSelected in listPlanets:

    params["COMMAND"] = planetSelected
    planet = planetSelected

    response = requests.post(url, data=params)
    #print(response.text)

    with open("data.txt", "a") as f:
        f.write("\n")
        f.write("Code: " + planet + "\n")
        f.write("Name: " + name(planet, response) + "\n")
        print(name(planet, response))
        f.write("Center Body: " + centerBody(planet, response) + "\n")
        f.write("Mass: " + mass(response) + "\n")
        f.write("Radius: " + radius(planet, response) + "\n")
        f.write("Axial Tilt: " + axialTilt(response) + "\n")
        f.write("Bond albedo: " + bondAlbedo(response) + "\n")
        f.write("Mean Solar Day: " + meanSolarDay(response) + "\n")
        f.write("Mean Temperature: " + temp(response) + "\n")
        f.write("Atmospheric Pressure: " + pressure(response) + "\n")

        X, Y, Z, VX, VY, VZ = posAndVel(response)
        f.write(f"X:  {X}\nY:  {Y}\nZ:  {Z}\nVX: {VX}\nVY: {VY}\nVZ: {VZ}\n")

print("\nFetching dwarf planet/minor bodies data from NASA...")

with open("data.txt", "a") as f:
    f.write("\nMINOR BDOIES/DWARF PLANETS")

for dwarfSelected in dwarfPlanets:

    params["COMMAND"] = dwarfSelected
    planet = dwarfSelected

    response = requests.post(url, data=params)
    #print(response.text)

    with open("data.txt", "a") as f:
        f.write("\n")
        f.write("Code: " + planet + "\n")
        f.write("Name: " + name(planet, response) + "\n")
        print(name(planet, response))
        f.write("Center Body: " + centerBody(planet, response) + "\n")

        X, Y, Z, VX, VY, VZ = posAndVel(response)
        f.write(f"X:  {X}\nY:  {Y}\nZ:  {Z}\nVX: {VX}\nVY: {VY}\nVZ: {VZ}\n")

print("\nFetching moon data from NASA...")

with open("data.txt", "a") as f:
    f.write("\n\nMOONS")

for moonSelected in listMoons:
    params["COMMAND"] = moonSelected
    planet = moonSelected

    response = requests.post(url, data=params)
    #print(response.text)


    with open("data.txt", "a") as f:
        f.write("\n")
        f.write("Code: " + planet + "\n")
        f.write("Name: " + name(planet, response) + "\n")
        print(name(planet, response))
        f.write("Center Body: " + centerBody(planet, response) + "\n")
        f.write("Mass: " + mass(response) + "\n")
        f.write("Radius: " + radius(planet, response) + "\n")
        f.write("Mean Solar Day: " + meanSolarDay(response) + "\n")
        f.write("Atmospheric Pressure: " + pressure(response) + "\n")

        X, Y, Z, VX, VY, VZ = posAndVel(response)
        f.write(f"X:  {X}\nY:  {Y}\nZ:  {Z}\nVX: {VX}\nVY: {VY}\nVZ: {VZ}\n")

print("\nFetching spacecraft data from NASA...")

with open("data.txt", "a") as f:
    f.write("\n\nSPACECRAFTS")

for spacecraftSelected in listSpacecraft:
    params["COMMAND"] = spacecraftSelected
    planet = spacecraftSelected

    response = requests.post(url, data=params)
    #print(response.text)
    
    with open("data.txt", "a") as f:
        f.write("\n")
        f.write("Code: " + planet + "\n")
        f.write("Name: " + name(planet, response) + "\n")
        print(name(planet, response))
        f.write("Center Body: " + centerBody(planet, response) + "\n")

        X, Y, Z, VX, VY, VZ = posAndVel(response)
        f.write(f"X:  {X}\nY:  {Y}\nZ:  {Z}\nVX: {VX}\nVY: {VY}\nVZ: {VZ}\n")

print("\n")