"""
NFPKG - A Python module for interacting with NewFramework packages & bundles
Author: DisabledMallis
"""

from zipfile import *

packageTypes = [
	"nkh",
	"jet",
	"assetbundles",
	"unpacked"
]

class PackageEntry:
	def __init__(self, path, data):
		self.path = path
		self.data = data

class Package:
	def __init__(self, filename, packageType="nkh"):
		self.filename = filename
		if packageType.lower() not in packageTypes:
			raise Exception("The packageType "+packageType+" is not a valid packageType!")
		self.packageType = packageType
		self.entries = []

	def Add(self, path, data):
		if not isinstance(data, bytes) and not isinstance(data, str):
			raise TypeError("data must be bytes or str!")
		packedFile = PackageEntry(path, data)
		self.entries.append(packedFile)

	def Store(self, security=b"Q%_{6#Px]]"):
		archive = ZipFile(self.filename, mode='w', compresslevel=ZIP_DEFLATED)
		archive.setpassword(security)
		for entry in self.entries:
			archive.writestr(entry.path, entry.data)
		archive.close()