"""
I rewrote this entire thing from the C++ code
- DisabledMallis
"""


mergeModes = [
	"INSERTIVE",
	"SUBSTITUTIVE"
]

def HasMergeMode(jsonObj):
	if jsonObj is dict:
		if "MERGE_MODE" in jsonObj:
			return True
	return False

def GetMergeMode(jsonObj):
	mergeMode = "SUBSTITUTIVE"
	if jsonObj is dict:
		if "MERGE_MODE" in jsonObj:
			if jsonObj["MERGE_MODE"] in mergeModes:
				mergeMode = jsonObj["MERGE_MODE"]
	return mergeMode

def isPrimitive(obj):
    return not hasattr(obj, '__dict__') and not type(obj) == dict and not type(obj) == list

def merge(base, next, mergeMode="SUBSTITUTIVE"):
	if HasMergeMode(next):
		mergeMode = GetMergeMode(next)
	
	result = base
	if next == None:
		if result == None:
			print("Please don't merge null documents!")
			raise Exception("Attempted to merge a pair of null documents")
		return result

	if result == None:
		return next

	if not type(result) == type(next):
		print("Please don't try to merge documents of differing types!")
		raise Exception("Attempted to merge documents of differing types")

	if isinstance(result, list) and isinstance(next, list):
		for i in range(len(next)):
			if next[i] == None:
				continue
			#Behavior on insertive mode only
			if mergeMode == "INSERTIVE":
				result.append(next[i])
				continue

			#Every other mode uses this logic
			if len(result) <= i:
				result.append(next[i])
				continue

			if isPrimitive(result[i]) and isPrimitive(next[i]):
				result[i] = next[i]
			if isinstance(result[i], list) and isinstance(next[i], list):
				result[i] = merge(result[i], next[i], mergeMode)
			if isinstance(result[i], dict) and isinstance(next[i], dict):
				result[i] = merge(result[i], next[i], mergeMode)
			if not type(result[i]) == type(next[i]):
				result[i] = next[i];

	if isinstance(result, dict) and isinstance(next, dict):
		if HasMergeMode(next):
			mergeMode = GetMergeMode(next)
		for key, value in next.items():
			if not key in result:
				result[key] = value
				continue

			#If it does have the key
			result[key] = merge(result[key], value, mergeMode)

	if isPrimitive(result) and isPrimitive(next):
		result = next

	return result;

def strip(base, next):
	result = next;
	needsInsertive = False

	if next == None:
		if result == None:
			print("Please don't strip null documents!")
			raise Exception("Attempted to strip a pair of null documents")
		return result

	if result == None:
		return next

	if not type(result) == type(next):
		print("Please don't try to strip documents of differing types!")
		raise Exception("Attempted to strip documents of differing types")

	if base == result:
		result = None
		return result, needsInsertive

	if isinstance(base, list):
		for x, y in zip(range(len(base)), range(len(next))):
			baseValue = base[x]
			nextValue = result[y]
			if not type(baseValue) == type(nextValue):
				print("Please don't try to strip lists of differing types!")
				raise Exception("Attempted to strip documents of differing types")
			if isinstance(baseValue, dict) or isinstance(baseValue, list):
				result[y], needsInsertive = strip(baseValue, nextValue)
				continue
			if baseValue == nextValue:
				result[y] = None
				continue

	if isinstance(base, dict):
		for key, value in base.items():
			if key in result:
				if result[key] == value:
					result.pop(key, None)
					continue
				if type(result[key]) != type(value):
					continue
				if (isinstance(result[key], dict) and isinstance(value, dict)) or (isinstance(result[key], list) and isinstance(value, list)):
					result[key], needsInsertive = strip(value, result[key])
					if needsInsertive and not HasMergeMode(result):
						result["MERGE_MODE"] = "INSERTIVE"

	return result, needsInsertive