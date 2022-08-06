"""
NFPKG - A Python module for interacting with NewFramework packages & bundles
Author: DisabledMallis
"""

import pyminizip
import os
from pathlib import *
from progress.bar import FillingSquaresBar

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
		self.level = 1;

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

		pwArg = ""
		if not self.security == None:
			pwArg = "-p"+self.security

		idx = 0
		idxEnd = len(self.pathsOnDisk)
		addBar = FillingSquaresBar('Packing files', max=idxEnd, suffix='%(percent)d%% (%(index)d/%(max)d)')
		toAdd = ""
		individualMode = False;
		for pathOnDisk, pathInArchive in zip(self.pathsOnDisk, self.pathsInArchive):
			toAdd = "\"" + pathOnDisk + "\" " + toAdd
			if idx % 50 == 0 and not individualMode:
				os.system("7z.exe a -tzip -mx"+str(self.level)+" "+self.filename+" "+toAdd+" "+pwArg+" > NUL")
				toAdd = ""
				idx = 0
				if idxEnd - idx < 50:
					individualMode = True
			if individualMode:
				os.system("7z.exe a -tzip -mx"+str(self.level)+" "+self.filename+" \""+pathOnDisk+"\" "+pwArg+" > NUL")
			addBar.next()
			idx += 1
		print()

		nameBar = FillingSquaresBar('Renaming files', max=len(self.pathsOnDisk), suffix='%(percent)d%% (%(index)d/%(max)d)')
		for pathOnDisk, pathInArchive in zip(self.pathsOnDisk, self.pathsInArchive):
			os.system("7z.exe rn "+self.filename+" \""+pathOnDisk+"\" \""+pathInArchive+"\" > NUL")
			nameBar.next()
		print()
		#pyminizip.compress_multiple(self.pathsOnDisk, self.dirsInArchive, self.filename, self.security, self.level)