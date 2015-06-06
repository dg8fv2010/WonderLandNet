#include "fileTransper.h"

bool TestCB::OnFile(OnFileStruct *onFileStruct)
{
// 	printf("OnFile: %i. (100%%) %i/%i %s %ib / %ib\n",
// 		onFileStruct->setID,
// 		onFileStruct->fileIndex+1,
// 		onFileStruct->numberOfFilesInThisSet,
// 		onFileStruct->fileName,
// 		onFileStruct->byteLengthOfThisFile,
// 		onFileStruct->byteLengthOfThisSet);


	//		FILE *fp = fopen(fileCopy.C_String(), "wb");
	FILE *fp=NULL;
	fopen_s(&fp,fileCopy.C_String(), "wb");
	fwrite(onFileStruct->fileData, onFileStruct->byteLengthOfThisFile, 1, fp);
	fclose(fp);

	// Make sure it worked
	unsigned int hash1 = SuperFastHashFile(file.C_String());
	if (RakNet::BitStream::DoEndianSwap())
		RakNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash1, sizeof(hash1));
	unsigned int hash2 = SuperFastHashFile(fileCopy.C_String());
	if (RakNet::BitStream::DoEndianSwap())
		RakNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash2, sizeof(hash2));
	RakAssert(hash1==hash2);

	// Return true to have RakNet delete the memory allocated to hold this file.
	// False if you hold onto the memory, and plan to delete it yourself later
	return true;
}


void TestCB::setFile(RakNet::RakString newFile)
{
	this->file=newFile;
}

void TestCB::setFileCopy(RakNet::RakString newFileCopy)
{
	this->fileCopy=newFileCopy;
}