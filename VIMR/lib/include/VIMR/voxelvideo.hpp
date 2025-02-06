#pragma once

#include <fstream>
#include "serializablemessage.hpp"
#include "vimr_api.hpp"

namespace VIMR {

  class VIMR_INTERFACE VoxelVideo {
   public:
    class VIMR_INTERFACE AudioStream {
     public:
      char * file_name{};
      char * voxel_label{};
      double * pose{};
      bool directional = false;
    };

    class VIMR_INTERFACE Metadata{
    public:
      AudioStream* astrms{};
      int astrm_cnt{};
      int total_frames{};
      double runtime_sec{};
      char* title{};
      char* date{};
      const char* base_audio_path{};
    };

    Metadata metadata;
    bool load_metadata_from_file(const char* _path);

    using field_int_t = int64_t;
    static constexpr field_int_t current_fmt_ver = 5;
    field_int_t format_version = current_fmt_ver;
    field_int_t frame_count{};
    field_int_t duration_ms{};
    field_int_t meta_start_offset = 16 + 3 * sizeof(field_int_t);
    field_int_t data_start_offset = meta_start_offset + 2 * sizeof(field_int_t);
    static bool is_voxvid(const char* _file_path);

   protected:
    static const char fmt_sig[16];
    std::fstream file_stream;
    std::fstream pose_file_stream;
    std::string parent_path;
    bool write_header();
    bool read_header();
    int load_all_frames(std::vector<VIMR::VoxelMessage>& _frames, std::function<void(int,int)> _progress_cb);
  };

}