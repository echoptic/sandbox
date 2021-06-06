from zipfile import ZipFile
import os
from os.path import basename

with ZipFile('bin.zip', 'w') as zipObj:
    for folderName, subfolders, filenames in os.walk('./bin'):
       for filename in filenames:
           filePath = os.path.join(folderName, filename)
           zipObj.write(filePath, basename(filePath))