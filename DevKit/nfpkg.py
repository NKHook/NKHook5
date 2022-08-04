"""
NFPKG - A Python module for interacting with NewFramework packages & bundles
Author: DisabledMallis
"""

import pyminizip
from pathlib import *

packageTypes = [
	"nkh",
	"jet",
	"assetbundles",
	"unpacked"
]

class Package:
	def __init__(self, filename, packageType="nkh", security="Q%_{6#Px]]"):
		self.filename = str(filename)
		if packageType.lower() not in packageTypes:
			raise Exception("The packageType "+packageType+" is not a valid packageType!")
		self.packageType = packageType
		self.security = security
		self.pathsOnDisk = []
		self.pathsInArchive = []
		self.dirsInArchive = []
		self.level = 0;

	def WriteIfAbsent(self, pathInArchive, pathOnDisk):
		exists = False
		for path in self.pathsInArchive:
			if path == pathInArchive:
				exists = True
		if not exists:
			self.Write(pathInArchive, pathOnDisk)

	def Write(self, pathInArchive, pathOnDisk):
		dirInArchive = str(Path(pathInArchive).parents[0])
		self.pathsOnDisk.append(str(pathOnDisk))
		self.pathsInArchive.append(str(pathInArchive))
		self.dirsInArchive.append(str(dirInArchive))

	def NkhMode(self):
		self.security = None;
		self.level = 9

	def Store(self):
		pyminizip.compress_multiple(self.pathsOnDisk, self.dirsInArchive, self.filename, self.security, self.level)