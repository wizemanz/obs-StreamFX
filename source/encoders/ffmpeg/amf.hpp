// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2020-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// AUTOGENERATED COPYRIGHT HEADER END

// THIS FEATURE IS DEPRECATED. SUBMITTED PATCHES WILL BE REJECTED.

#pragma once
#include "encoders/encoder-ffmpeg.hpp"
#include "encoders/ffmpeg/handler.hpp"

#include "warning-disable.hpp"
#include <cinttypes>
extern "C" {
#include <libavcodec/avcodec.h>
}
#include "warning-enable.hpp"

/* Parameters by their codec specific name.
 * '#' denotes a parameter specified via the context itself.

H.264			H.265				Options							Done?
usage			usage				transcoding						--
preset			preset				speed,balanced,quality			Defines
profile			profile				<different>						Defines
level			level				<different>						Defines
				tier				main,high
rc				rc					cqp,cbr,vbr_peak,vbr_latency	Defines
preanalysis		preanalysis			false,true						Defines
vbaq			vbaq				false,true						Defines
enforce_hrd		enforce_hrd			false,true						Defines
filler_data		filler_data			false,true						--
frame_skipping	skip_frame			false,true						Defines
qp_i			qp_i				range(-1 - 51)					Defines
qp_p			qp_p				range(-1 - 51)					Defines
qp_b								range(-1 - 51)					Defines
#max_b_frames														Defines
bf_delta_qp							range(-10 - 10)					--
bf_ref								false,true						Defines
bf_ref_delta_qp						range(-10 - 10)					--
me_half_pel		me_half_pel			false,true						--
me_quarter_pel	me_quarter_pel		false,true						--
aud				aud					false,true						Defines
max_au_size		max_au_size			range(0 - Inf)					--
#refs								range(0 - 16?)					Defines
#color_range						AVCOL_RANGE_JPEG				FFmpeg
#bit_rate															Defines
#rc_max_rate														Defines
#rc_buffer_size														Defines
#rc_initial_buffer_occupancy										--
#flags								AV_CODEC_FLAG_LOOP_FILTER		--
#gop_size															FFmpeg
*/

// AMF H.264
// intra_refresh_mb: 0 - Inf
// header_spacing: -1 - 1000
// coder: auto, cavlc, cabac
// qmin, qmax (HEVC uses its own settings)

// AMF H.265
// header_insertion_mode: none, gop, idr
// gops_per_idr: 0 - Inf
// min_qp_i: -1 - 51
// max_qp_i: -1 - 51
// min_qp_p: -1 - 51
// max_qp_p: -1 - 51

namespace streamfx::encoder::ffmpeg {
	namespace amf {
		enum class preset : int32_t {
			SPEED,
			BALANCED,
			QUALITY,
			INVALID = -1,
		};

		enum class ratecontrolmode : int64_t {
			CQP,
			CBR,
			VBR_PEAK,
			VBR_LATENCY,
			INVALID = -1,
		};

		extern std::map<preset, std::string> presets;

		extern std::map<preset, std::string> preset_to_opt;

		extern std::map<ratecontrolmode, std::string> ratecontrolmodes;

		extern std::map<ratecontrolmode, std::string> ratecontrolmode_to_opt;

		bool is_available();

		void defaults(ffmpeg_factory* factory, obs_data_t* settings);
		void properties_before(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props);
		void properties_after(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props);
		void properties_runtime(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props);
		void migrate(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, uint64_t version);
		void update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings);
		void override_update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings);
		void log(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings);

	} // namespace amf

	class amf_h264 : public handler {
		public:
		amf_h264();
		virtual ~amf_h264();

		bool has_keyframes(ffmpeg_factory* instance) override;
		bool is_hardware(ffmpeg_factory* instance) override;
		bool has_threading(ffmpeg_factory* instance) override;

		void adjust_info(ffmpeg_factory* factory, std::string& id, std::string& name, std::string& codec) override;

		virtual std::string help(ffmpeg_factory* factory) override
		{
			return "https://github.com/Xaymar/obs-StreamFX/wiki/Encoder-FFmpeg-AMF";
		};

		void defaults(ffmpeg_factory* factory, obs_data_t* settings) override;
		void properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props) override;
		void migrate(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, uint64_t version) override;
		void update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings) override;
		void override_update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings) override;
		void log(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings) override;

		void override_colorformat(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, AVPixelFormat& target_format) override;

		private:
		void get_encoder_properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props);
		void get_runtime_properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props);
	};

	class amf_hevc : public handler {
		public:
		amf_hevc();
		virtual ~amf_hevc();

		bool has_keyframes(ffmpeg_factory* instance) override;
		bool is_hardware(ffmpeg_factory* instance) override;
		bool has_threading(ffmpeg_factory* instance) override;

		void adjust_info(ffmpeg_factory* factory, std::string& id, std::string& name, std::string& codec) override;

		std::string help(ffmpeg_factory* factory) override
		{
			return "https://github.com/Xaymar/obs-StreamFX/wiki/Encoder-FFmpeg-AMF";
		};

		void defaults(ffmpeg_factory* factory, obs_data_t* settings) override;
		void properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props) override;
		void migrate(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, uint64_t version) override;
		void update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings) override;
		void override_update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings) override;
		void log(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings) override;

		private:
		void get_encoder_properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props);
		void get_runtime_properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props);
	};
} // namespace streamfx::encoder::ffmpeg
