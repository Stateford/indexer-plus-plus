// This file is the part of the Indexer++ project.
// Copyright (C) 2016 Anna Krykora <krykoraanna@gmail.com>. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be found in the LICENSE file.

#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "MFTReadResult.h"
#include "Macros.h"
#include "WindowsWrapper.h"
#include "typedefs.h"

#include "MFTReader.h"
#include "RawMFTRecordsParser.h"

namespace ntfs_reader {

    class WinApiCommon;

	// Reads and parses raw disk data into FileInfo objects.

    class RawMFTReader : public MFTReader {
       public:
        explicit RawMFTReader(char drive_letter);

        NO_COPY(RawMFTReader)

        ~RawMFTReader() = default;

		virtual std::unique_ptr<indexer_common::MFTReadResult> ReadAllRecords() override;

       private:
        // Gets the basic volume info such as how many bytes per cluster, first MFT logical cluster number, MFT record size.

        bool GetNtfsVolumeData(NTFS_VOLUME_DATA_BUFFER* volume_data_buff) const;


        // Sets the read location on the physical drive.

		void SetVolumePointerFromVolumeBegin(indexer_common::uint64 bytes_to_move) const;


		std::unique_ptr<std::vector<std::pair<indexer_common::int64, indexer_common::int64>>> GetMFTRetrievalPointers(char* buff) const;


		static void FindAndSetRoot(const std::vector<indexer_common::FileInfo*>& file_infos, indexer_common::MFTReadResult* result, char drive_letter);


        // Handle of the volume with custom smart pointer deleter.

        std::unique_ptr<void, std::function<void(HANDLE)>> volume_;


        VolumeData volume_data_;


        std::unique_ptr<RawMFTRecordsParser> u_records_parser_;


        // Indicates whether to read previously serialized volume MFT from file.

        bool read_serialized_mft_;


        // Indicates whether to serialize raw MFT data to file.

        bool save_raw_mft_;

		static const indexer_common::uint kBufferSize;
    };

} // namespace ntfs_reader