#pragma once

#include "RakPeerInterface.h"
#include "FileListTransfer.h"
#include "RakSleep.h"

#include "MessageIdentifiers.h"
#include "FileListTransferCBInterface.h"
#include "FileOperations.h"
#include "SuperFastHash.h"
#include "RakAssert.h"
#include "BitStream.h"
#include "IncrementalReadInterface.h"
#include "PacketizedTCP.h"
#include "SocketLayer.h"
#include <stdio.h>
#include "Gets.h"

class TestCB : public RakNet::FileListTransferCBInterface
{
public:
	bool OnFile(OnFileStruct *onFileStruct);

	virtual void OnFileProgress(FileProgressStruct *fps)
	{
// 		printf("OnFileProgress: %i partCount=%i partTotal=%i (%i%%) %i/%i %s %ib/%ib %ib/%ib total\n",
// 			fps->onFileStruct->setID,
// 			fps->partCount, fps->partTotal, (int) (100.0*(double)fps->onFileStruct->bytesDownloadedForThisFile/(double)fps->onFileStruct->byteLengthOfThisFile),
// 			fps->onFileStruct->fileIndex+1,
// 			fps->onFileStruct->numberOfFilesInThisSet,
// 			fps->onFileStruct->fileName,
// 			fps->onFileStruct->bytesDownloadedForThisFile,
// 			fps->onFileStruct->byteLengthOfThisFile,
// 			fps->onFileStruct->bytesDownloadedForThisSet,
// 			fps->onFileStruct->byteLengthOfThisSet,
// 			fps->firstDataChunk);
	}

	virtual bool OnDownloadComplete(DownloadCompleteStruct *dcs)
	{
		printf("Download complete.\n");

		// Returning false automatically deallocates the automatically allocated handler that was created by DirectoryDeltaTransfer
		return false;
	}

	void setFile(RakNet::RakString newFile);

	void setFileCopy(RakNet::RakString newFileCopy);
	
private:
	RakNet::RakString file;
	RakNet::RakString fileCopy;
}/*transferCallback*/;
