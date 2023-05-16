// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// AUTOGENERATED COPYRIGHT HEADER END
// Copyright (C) 2020-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>

//--------------------------------------------------------------------------------//
// THIS FEATURE IS DEPRECATED. SUBMITTED PATCHES WILL BE REJECTED.
//--------------------------------------------------------------------------------//

#include "amf.hpp"
#include "common.hpp"
#include "strings.hpp"
#include "encoders/codecs/h264.hpp"
#include "encoders/codecs/hevc.hpp"
#include "encoders/encoder-ffmpeg.hpp"
#include "ffmpeg/tools.hpp"
#include "plugin.hpp"

#include "warning-disable.hpp"
extern "C" {
#include <libavutil/opt.h>
}
#include "warning-enable.hpp"

// Translation
#define ST_I18N "Encoder.FFmpeg.AMF"
#define ST_I18N_DEPRECATED ST_I18N ".Deprecated"
#define ST_I18N_PRESET ST_I18N ".Preset"
#define ST_I18N_PRESET_(x) ST_I18N_PRESET "." x
#define ST_I18N_RATECONTROL "Encoder.FFmpeg.AMF.RateControl"
#define ST_I18N_RATECONTROL_MODE ST_I18N_RATECONTROL ".Mode"
#define ST_I18N_RATECONTROL_MODE_(x) ST_I18N_RATECONTROL_MODE "." x
#define ST_I18N_RATECONTROL_LOOKAHEAD ST_I18N_RATECONTROL ".LookAhead"
#define ST_I18N_RATECONTROL_FRAMESKIPPING ST_I18N_RATECONTROL ".FrameSkipping"
#define ST_I18N_RATECONTROL_LIMITS ST_I18N_RATECONTROL ".Limits"
#define ST_I18N_RATECONTROL_LIMITS_BUFFERSIZE ST_I18N_RATECONTROL_LIMITS ".BufferSize"
#define ST_I18N_RATECONTROL_LIMITS_BITRATE ST_I18N_RATECONTROL_LIMITS ".Bitrate"
#define ST_I18N_RATECONTROL_LIMITS_BITRATE_TARGET ST_I18N_RATECONTROL_LIMITS_BITRATE ".Target"
#define ST_I18N_RATECONTROL_LIMITS_BITRATE_MAXIMUM ST_I18N_RATECONTROL_LIMITS_BITRATE ".Maximum"
#define ST_I18N_RATECONTROL_QP ST_I18N_RATECONTROL ".QP"
#define ST_I18N_RATECONTROL_QP_I ST_I18N_RATECONTROL_QP ".I"
#define ST_I18N_RATECONTROL_QP_P ST_I18N_RATECONTROL_QP ".P"
#define ST_I18N_RATECONTROL_QP_B ST_I18N_RATECONTROL_QP ".B"
#define ST_I18N_OTHER ST_I18N ".Other"
#define ST_I18N_OTHER_BFRAMES ST_I18N_OTHER ".BFrames"
#define ST_I18N_OTHER_BFRAMEREFERENCES ST_I18N_OTHER ".BFrameReferences"
#define ST_I18N_OTHER_REFERENCEFRAMES ST_I18N_OTHER ".ReferenceFrames"
#define ST_I18N_OTHER_ENFORCEHRD ST_I18N_OTHER ".EnforceHRD"
#define ST_I18N_OTHER_VBAQ ST_I18N_OTHER ".VBAQ"
#define ST_I18N_OTHER_ACCESSUNITDELIMITER ST_I18N_OTHER ".AccessUnitDelimiter"

// Settings
#define ST_KEY_PRESET "Preset"
#define ST_KEY_RATECONTROL_MODE "RateControl.Mode"
#define ST_KEY_RATECONTROL_LOOKAHEAD "RateControl.LookAhead"
#define ST_KEY_RATECONTROL_FRAMESKIPPING "RateControl.FrameSkipping"
#define ST_KEY_RATECONTROL_LIMITS_BUFFERSIZE "RateControl.Limits.BufferSize"
#define ST_KEY_RATECONTROL_LIMITS_BITRATE_TARGET "RateControl.Limits.Bitrate.Target"
#define ST_KEY_RATECONTROL_LIMITS_BITRATE_MAXIMUM "RateControl.Limits.Bitrate.Maximum"
#define ST_KEY_RATECONTROL_QP_I "RateControl.QP.I"
#define ST_KEY_RATECONTROL_QP_P "RateControl.QP.P"
#define ST_KEY_RATECONTROL_QP_B "RateControl.QP.B"
#define ST_KEY_OTHER_BFRAMES "Other.BFrames"
#define ST_KEY_OTHER_BFRAMEREFERENCES "Other.BFrameReferences"
#define ST_KEY_OTHER_REFERENCEFRAMES "Other.ReferenceFrames"
#define ST_KEY_OTHER_ENFORCEHRD "Other.EnforceHRD"
#define ST_KEY_OTHER_VBAQ "Other.VBAQ"
#define ST_KEY_OTHER_ACCESSUNITDELIMITER "Other.AccessUnitDelimiter"

// Settings
#define ST_KEY_H264_PROFILE "H264.Profile"
#define ST_KEY_H264_LEVEL "H264.Level"

// Settings
#define ST_KEY_HEVC_PROFILE "H265.Profile"
#define ST_KEY_HEVC_TIER "H265.Tier"
#define ST_KEY_HEVC_LEVEL "H265.Level"

using namespace streamfx::encoder::ffmpeg;
using namespace streamfx::encoder::codec;

std::map<amf::preset, std::string> amf::presets{
	{amf::preset::SPEED, ST_I18N_PRESET_("Speed")},
	{amf::preset::BALANCED, ST_I18N_PRESET_("Balanced")},
	{amf::preset::QUALITY, ST_I18N_PRESET_("Quality")},
};

std::map<amf::preset, std::string> amf::preset_to_opt{
	{amf::preset::SPEED, "speed"},
	{amf::preset::BALANCED, "balanced"},
	{amf::preset::QUALITY, "quality"},
};

std::map<amf::ratecontrolmode, std::string> amf::ratecontrolmodes{
	{amf::ratecontrolmode::CQP, ST_I18N_RATECONTROL_MODE_("CQP")},
	{amf::ratecontrolmode::CBR, ST_I18N_RATECONTROL_MODE_("CBR")},
	{amf::ratecontrolmode::VBR_PEAK, ST_I18N_RATECONTROL_MODE_("VBR_PEAK")},
	{amf::ratecontrolmode::VBR_LATENCY, ST_I18N_RATECONTROL_MODE_("VBR_LATENCY")},
};

std::map<amf::ratecontrolmode, std::string> amf::ratecontrolmode_to_opt{
	{amf::ratecontrolmode::CQP, "cqp"},
	{amf::ratecontrolmode::CBR, "cbr"},
	{amf::ratecontrolmode::VBR_PEAK, "vbr_peak"},
	{amf::ratecontrolmode::VBR_LATENCY, "vbr_latency"},
};

static std::map<h264::profile, std::string> h264_profiles{
	{h264::profile::CONSTRAINED_BASELINE, "constrained_baseline"},
	{h264::profile::MAIN, "main"},
	{h264::profile::HIGH, "high"},
};

static std::map<h264::level, std::string> h264_levels{
	{h264::level::L1_0, "1.0"}, {h264::level::L1_0b, "1.0b"}, {h264::level::L1_1, "1.1"}, {h264::level::L1_2, "1.2"}, {h264::level::L1_3, "1.3"}, {h264::level::L2_0, "2.0"}, {h264::level::L2_1, "2.1"}, {h264::level::L2_2, "2.2"}, {h264::level::L3_0, "3.0"}, {h264::level::L3_1, "3.1"}, {h264::level::L3_2, "3.2"}, {h264::level::L4_0, "4.0"}, {h264::level::L4_1, "4.1"}, {h264::level::L4_2, "4.2"}, {h264::level::L5_0, "5.0"}, {h264::level::L5_1, "5.1"}, {h264::level::L5_2, "5.2"}, {h264::level::L6_0, "6.0"}, {h264::level::L6_1, "6.1"}, {h264::level::L6_2, "6.2"},
};

static std::map<hevc::profile, std::string> hevc_profiles{
	{hevc::profile::MAIN, "main"},
};

static std::map<hevc::tier, std::string> hevc_tiers{
	{hevc::tier::MAIN, "main"},
	{hevc::tier::HIGH, "high"},
};

static std::map<hevc::level, std::string> hevc_levels{
	{hevc::level::L1_0, "1.0"}, {hevc::level::L2_0, "2.0"}, {hevc::level::L2_1, "2.1"}, {hevc::level::L3_0, "3.0"}, {hevc::level::L3_1, "3.1"}, {hevc::level::L4_0, "4.0"}, {hevc::level::L4_1, "4.1"}, {hevc::level::L5_0, "5.0"}, {hevc::level::L5_1, "5.1"}, {hevc::level::L5_2, "5.2"}, {hevc::level::L6_0, "6.0"}, {hevc::level::L6_1, "6.1"}, {hevc::level::L6_2, "6.2"},
};

bool streamfx::encoder::ffmpeg::amf::is_available()
{
#if defined(D_PLATFORM_WINDOWS)
#if defined(D_PLATFORM_64BIT)
	std::filesystem::path lib_name = std::filesystem::u8path("amfrt64.dll");
#else
	std::filesystem::path lib_name = std::filesystem::u8path("amfrt32.dll");
#endif
#elif defined(D_PLATFORM_LINUX)
#if defined(D_PLATFORM_64BIT)
	std::filesystem::path lib_name = std::filesystem::u8path("libamfrt64.so.1");
#else
	std::filesystem::path lib_name = std::filesystem::u8path("libamfrt32.so.1");
#endif
#endif
	try {
		streamfx::util::library::load(lib_name);
		return true;
	} catch (...) {
		return false;
	}
}

void amf::defaults(ffmpeg_factory* factory, obs_data_t* settings)
{
	obs_data_set_default_int(settings, ST_KEY_PRESET, static_cast<int64_t>(amf::preset::BALANCED));

	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_MODE, static_cast<int64_t>(ratecontrolmode::CBR));
	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_LOOKAHEAD, -1);
	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_FRAMESKIPPING, -1);
	//ob
	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_LIMITS_BITRATE_TARGET, 6000);
	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_LIMITS_BITRATE_MAXIMUM, 0);
	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_LIMITS_BUFFERSIZE, 12000);

	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_QP_I, -1);
	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_QP_P, -1);
	obs_data_set_default_int(settings, ST_KEY_RATECONTROL_QP_B, -1);

	obs_data_set_default_int(settings, ST_KEY_OTHER_BFRAMES, -1);
	obs_data_set_default_int(settings, ST_KEY_OTHER_BFRAMEREFERENCES, -1);
	obs_data_set_default_int(settings, ST_KEY_OTHER_REFERENCEFRAMES, -1);
	obs_data_set_default_int(settings, ST_KEY_OTHER_ENFORCEHRD, -1);
	obs_data_set_default_int(settings, ST_KEY_OTHER_VBAQ, -1);
	obs_data_set_default_int(settings, ST_KEY_OTHER_ACCESSUNITDELIMITER, -1);

	// Replay Buffer
	obs_data_set_default_int(settings, "bitrate", 0);
}

static bool modified_ratecontrol(obs_properties_t* props, obs_property_t*, obs_data_t* settings) noexcept
{
	bool have_bitrate       = false;
	bool have_bitrate_range = false;
	bool have_qp            = false;

	amf::ratecontrolmode rc = static_cast<amf::ratecontrolmode>(obs_data_get_int(settings, ST_KEY_RATECONTROL_MODE));
	switch (rc) {
	case amf::ratecontrolmode::CQP:
		have_qp = true;
		break;
	case amf::ratecontrolmode::INVALID:
	case amf::ratecontrolmode::CBR:
		have_bitrate = true;
		break;
	case amf::ratecontrolmode::VBR_PEAK:
	case amf::ratecontrolmode::VBR_LATENCY:
		have_bitrate       = true;
		have_bitrate_range = true;
		break;
	}

	obs_property_set_visible(obs_properties_get(props, ST_I18N_RATECONTROL_LIMITS), have_bitrate);
	obs_property_set_visible(obs_properties_get(props, ST_KEY_RATECONTROL_LIMITS_BUFFERSIZE), have_bitrate);
	obs_property_set_visible(obs_properties_get(props, ST_KEY_RATECONTROL_LIMITS_BITRATE_TARGET), have_bitrate);
	obs_property_set_visible(obs_properties_get(props, ST_KEY_RATECONTROL_LIMITS_BITRATE_MAXIMUM), have_bitrate_range);

	obs_property_set_visible(obs_properties_get(props, ST_I18N_RATECONTROL_QP), have_qp);
	obs_property_set_visible(obs_properties_get(props, ST_KEY_RATECONTROL_QP_I), have_qp);
	obs_property_set_visible(obs_properties_get(props, ST_KEY_RATECONTROL_QP_P), have_qp);
	obs_property_set_visible(obs_properties_get(props, ST_KEY_RATECONTROL_QP_B), have_qp);

	return true;
}

void amf::properties_before(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	{
		auto p = obs_properties_add_text(props, "[[deprecated]]", D_TRANSLATE(ST_I18N_DEPRECATED), OBS_TEXT_INFO);
		obs_property_text_set_info_type(p, OBS_TEXT_INFO_WARNING);
		obs_property_text_set_info_word_wrap(p, true);
	}

	auto p = obs_properties_add_list(props, ST_KEY_PRESET, D_TRANSLATE(ST_I18N_PRESET), OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	for (auto kv : presets) {
		obs_property_list_add_int(p, D_TRANSLATE(kv.second.c_str()), static_cast<int64_t>(kv.first));
	}
}

void amf::properties_after(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	auto codec = factory->get_avcodec();

	{ // Rate Control
		obs_properties_t* grp = obs_properties_create();
		obs_properties_add_group(props, ST_I18N_RATECONTROL, D_TRANSLATE(ST_I18N_RATECONTROL), OBS_GROUP_NORMAL, grp);

		{
			auto p = obs_properties_add_list(grp, ST_KEY_RATECONTROL_MODE, D_TRANSLATE(ST_I18N_RATECONTROL_MODE), OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
			obs_property_set_modified_callback(p, modified_ratecontrol);
			for (auto kv : ratecontrolmodes) {
				obs_property_list_add_int(p, D_TRANSLATE(kv.second.c_str()), static_cast<int64_t>(kv.first));
			}
		}

		streamfx::util::obs_properties_add_tristate(grp, ST_KEY_RATECONTROL_LOOKAHEAD, D_TRANSLATE(ST_I18N_RATECONTROL_LOOKAHEAD));
		streamfx::util::obs_properties_add_tristate(grp, ST_KEY_RATECONTROL_FRAMESKIPPING, D_TRANSLATE(ST_I18N_RATECONTROL_FRAMESKIPPING));
	}

	{
		obs_properties_t* grp = obs_properties_create();
		obs_properties_add_group(props, ST_I18N_RATECONTROL_LIMITS, D_TRANSLATE(ST_I18N_RATECONTROL_LIMITS), OBS_GROUP_NORMAL, grp);

		{
			auto p = obs_properties_add_int(grp, ST_KEY_RATECONTROL_LIMITS_BITRATE_TARGET, D_TRANSLATE(ST_I18N_RATECONTROL_LIMITS_BITRATE_TARGET), -1, std::numeric_limits<std::int32_t>::max(), 1);
			obs_property_int_set_suffix(p, " kbit/s");
		}

		{
			auto p = obs_properties_add_int(grp, ST_KEY_RATECONTROL_LIMITS_BITRATE_MAXIMUM, D_TRANSLATE(ST_I18N_RATECONTROL_LIMITS_BITRATE_MAXIMUM), -1, std::numeric_limits<std::int32_t>::max(), 1);
			obs_property_int_set_suffix(p, " kbit/s");
		}

		{
			auto p = obs_properties_add_int(grp, ST_KEY_RATECONTROL_LIMITS_BUFFERSIZE, D_TRANSLATE(ST_I18N_RATECONTROL_LIMITS_BUFFERSIZE), 0, std::numeric_limits<std::int32_t>::max(), 1);
			obs_property_int_set_suffix(p, " kbit");
		}
	}

	{
		obs_properties_t* grp = obs_properties_create();
		obs_properties_add_group(props, ST_I18N_RATECONTROL_QP, D_TRANSLATE(ST_I18N_RATECONTROL_QP), OBS_GROUP_NORMAL, grp);

		obs_properties_add_int_slider(grp, ST_KEY_RATECONTROL_QP_I, D_TRANSLATE(ST_I18N_RATECONTROL_QP_I), -1, 51, 1);
		obs_properties_add_int_slider(grp, ST_KEY_RATECONTROL_QP_P, D_TRANSLATE(ST_I18N_RATECONTROL_QP_P), -1, 51, 1);

		if (std::string_view("amf_h264") == codec->name) {
			obs_properties_add_int_slider(grp, ST_KEY_RATECONTROL_QP_B, D_TRANSLATE(ST_I18N_RATECONTROL_QP_B), -1, 51, 1);
		}
	}

	{
		obs_properties_t* grp = obs_properties_create();
		obs_properties_add_group(props, ST_I18N_OTHER, D_TRANSLATE(ST_I18N_OTHER), OBS_GROUP_NORMAL, grp);

		{
			auto p = obs_properties_add_int_slider(grp, ST_KEY_OTHER_BFRAMES, D_TRANSLATE(ST_I18N_OTHER_BFRAMES), -1, 4, 1);
			obs_property_int_set_suffix(p, " frames");
		}

		streamfx::util::obs_properties_add_tristate(grp, ST_KEY_OTHER_BFRAMEREFERENCES, D_TRANSLATE(ST_I18N_OTHER_BFRAMEREFERENCES));
		{
			auto p = obs_properties_add_int_slider(grp, ST_KEY_OTHER_REFERENCEFRAMES, D_TRANSLATE(ST_I18N_OTHER_REFERENCEFRAMES), -1, 16, 1);
			obs_property_int_set_suffix(p, " frames");
		}
		streamfx::util::obs_properties_add_tristate(grp, ST_KEY_OTHER_ENFORCEHRD, D_TRANSLATE(ST_I18N_OTHER_ENFORCEHRD));
		streamfx::util::obs_properties_add_tristate(grp, ST_KEY_OTHER_VBAQ, D_TRANSLATE(ST_I18N_OTHER_VBAQ));
		streamfx::util::obs_properties_add_tristate(grp, ST_KEY_OTHER_ACCESSUNITDELIMITER, D_TRANSLATE(ST_I18N_OTHER_ACCESSUNITDELIMITER));
	}
}

void amf::properties_runtime(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props) {}

void amf::migrate(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, uint64_t version) {}

void amf::update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	auto codec   = factory->get_avcodec();
	auto context = instance->get_avcodeccontext();

	// Alway enable loop filter.
	context->flags |= AV_CODEC_FLAG_LOOP_FILTER;

	// Always transcoding. Other usage options cause problems.
	av_opt_set(context->priv_data, "usage", "transcoding", AV_OPT_SEARCH_CHILDREN);

	{ // Presets
		preset c_preset = static_cast<preset>(obs_data_get_int(settings, ST_KEY_PRESET));
		auto   found    = preset_to_opt.find(c_preset);
		if (found != preset_to_opt.end()) {
			av_opt_set(context->priv_data, "quality", found->second.c_str(), AV_OPT_SEARCH_CHILDREN);
		} else {
			av_opt_set(context->priv_data, "quality", nullptr, AV_OPT_SEARCH_CHILDREN);
		}
	}

	{ // Rate Control
		bool have_bitrate       = false;
		bool have_bitrate_range = false;
		bool have_qp            = false;

		ratecontrolmode rc    = static_cast<ratecontrolmode>(obs_data_get_int(settings, ST_KEY_RATECONTROL_MODE));
		auto            rcopt = ratecontrolmode_to_opt.find(rc);
		if (rcopt != ratecontrolmode_to_opt.end()) {
			av_opt_set(context->priv_data, "rc", rcopt->second.c_str(), AV_OPT_SEARCH_CHILDREN);
		} else {
			have_bitrate = true;
			av_opt_set(context->priv_data, "rc", "cbr", AV_OPT_SEARCH_CHILDREN);
		}

		av_opt_set_int(context->priv_data, "filler_data", 0, AV_OPT_SEARCH_CHILDREN);
		switch (rc) {
		case ratecontrolmode::CQP:
			have_qp = true;
			break;
		case ratecontrolmode::INVALID:
		case ratecontrolmode::CBR:
			have_bitrate = true;
			av_opt_set_int(context->priv_data, "filler_data", 1, AV_OPT_SEARCH_CHILDREN);
			break;
		case ratecontrolmode::VBR_PEAK:
		case ratecontrolmode::VBR_LATENCY:
			have_bitrate_range = true;
			have_bitrate       = true;
			break;
		}

		// Look Ahead (Pre-analysis, single frame lookahead)
		if (int la = static_cast<int>(obs_data_get_int(settings, ST_KEY_RATECONTROL_LOOKAHEAD)); !streamfx::util::is_tristate_default(la)) {
			av_opt_set_int(context->priv_data, "preanalysis", la, AV_OPT_SEARCH_CHILDREN);
		}

		// Frame Skipping (Drop frames to maintain bitrate limits)
		if (int la = static_cast<int>(obs_data_get_int(settings, ST_KEY_RATECONTROL_FRAMESKIPPING)); !streamfx::util::is_tristate_default(la)) {
			if (std::string_view("amf_h264") == codec->name) {
				av_opt_set_int(context->priv_data, "frame_skipping", la, AV_OPT_SEARCH_CHILDREN);
			} else {
				av_opt_set_int(context->priv_data, "skip_frame", la, AV_OPT_SEARCH_CHILDREN);
			}
		}

		if (have_bitrate) {
			int64_t v = obs_data_get_int(settings, ST_KEY_RATECONTROL_LIMITS_BITRATE_TARGET);
			if (v > -1) {
				context->bit_rate    = static_cast<int>(v * 1000);
				context->rc_max_rate = context->bit_rate;

				// Support for Replay Buffer
				obs_data_set_int(settings, "bitrate", v);
			} else {
				obs_data_set_int(settings, "bitrate", context->bit_rate);
			}
		} else {
			context->bit_rate = 0;
		}
		if (have_bitrate_range) {
			if (int64_t max = obs_data_get_int(settings, ST_KEY_RATECONTROL_LIMITS_BITRATE_MAXIMUM); max > -1)
				context->rc_max_rate = static_cast<int>(max * 1000);
		} else {
			context->rc_max_rate = 0;
		}

		// Buffer Size
		if (have_bitrate || have_bitrate_range) {
			if (int64_t v = obs_data_get_int(settings, ST_KEY_RATECONTROL_LIMITS_BUFFERSIZE); v > -1)
				context->rc_buffer_size = static_cast<int>(v * 1000);
		} else {
			context->rc_buffer_size = 0;
		}

		// QP Settings
		if (have_qp) {
			if (int64_t qp = obs_data_get_int(settings, ST_KEY_RATECONTROL_QP_I); qp > -1) {
				av_opt_set_int(context->priv_data, "qp_i", static_cast<int>(qp), AV_OPT_SEARCH_CHILDREN);
			}
			if (int64_t qp = obs_data_get_int(settings, ST_KEY_RATECONTROL_QP_P); qp > -1) {
				av_opt_set_int(context->priv_data, "qp_p", static_cast<int>(qp), AV_OPT_SEARCH_CHILDREN);
			}
			if (std::string_view("amf_h264") == codec->name) {
				if (int64_t qp = obs_data_get_int(settings, ST_KEY_RATECONTROL_QP_B); qp > -1) {
					av_opt_set_int(context->priv_data, "qp_b", static_cast<int>(qp), AV_OPT_SEARCH_CHILDREN);
				}
			}
		}
	}

	{ // Other
		if (std::string_view("amf_h264") == codec->name) {
			if (int64_t bf = obs_data_get_int(settings, ST_KEY_OTHER_BFRAMES); bf > -1) {
				context->max_b_frames = static_cast<int>(bf);
			}
			if (int64_t zl = obs_data_get_int(settings, ST_KEY_OTHER_BFRAMEREFERENCES); !streamfx::util::is_tristate_default(zl)) {
				av_opt_set_int(context->priv_data, "bf_ref", zl, AV_OPT_SEARCH_CHILDREN);
			}
		}

		if (int64_t refs = obs_data_get_int(settings, ST_KEY_OTHER_REFERENCEFRAMES); refs > -1) {
			context->refs = static_cast<int>(refs);
		}

		if (int64_t v = obs_data_get_int(settings, ST_KEY_OTHER_ENFORCEHRD); !streamfx::util::is_tristate_default(v)) {
			av_opt_set_int(context->priv_data, "enforce_hrd", v, AV_OPT_SEARCH_CHILDREN);
		}

		if (int64_t v = obs_data_get_int(settings, ST_KEY_OTHER_VBAQ); !streamfx::util::is_tristate_default(v)) {
			av_opt_set_int(context->priv_data, "vbaq", v, AV_OPT_SEARCH_CHILDREN);
		}

		if (int64_t v = obs_data_get_int(settings, ST_KEY_OTHER_ACCESSUNITDELIMITER); !streamfx::util::is_tristate_default(v)) {
			av_opt_set_int(context->priv_data, "aud", v, AV_OPT_SEARCH_CHILDREN);
		}

		av_opt_set_int(context->priv_data, "me_half_pel", 1, AV_OPT_SEARCH_CHILDREN);
		av_opt_set_int(context->priv_data, "me_quarter_pel", 1, AV_OPT_SEARCH_CHILDREN);
	}
}

void amf::override_update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings) {}

void amf::log(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	using namespace ::streamfx::ffmpeg;

	auto codec   = factory->get_avcodec();
	auto context = instance->get_avcodeccontext();

	DLOG_INFO("[%s]   AMD AMF:", codec->name);
	tools::print_av_option_string2(context, "usage", "    Usage", [](int64_t v, std::string_view o) { return std::string(o); });
	tools::print_av_option_string2(context, "quality", "    Preset", [](int64_t v, std::string_view o) { return std::string(o); });
	tools::print_av_option_string2(context, "rc", "    Rate Control", [](int64_t v, std::string_view o) { return std::string(o); });
	tools::print_av_option_bool(context, "preanalysis", "      Look-Ahead");
	if (std::string_view("amf_h264") == codec->name) {
		tools::print_av_option_bool(context, "frame_skipping", "      Frame Skipping");
	} else {
		tools::print_av_option_bool(context, "skip_frame", "      Frame Skipping");
	}
	tools::print_av_option_bool(context, "filler_data", "      Filler Data");

	DLOG_INFO("[%s]       Bitrate:", codec->name);
	tools::print_av_option_int(context, "b", "        Target", "bits/sec");
	tools::print_av_option_int(context, "maxrate", "        Maximum", "bits/sec");
	tools::print_av_option_int(context, "bufsize", "        Buffer", "bits");
	DLOG_INFO("[%s]       Quantization Parameters:", codec->name);
	tools::print_av_option_int(context, "qp_i", "        I-Frame", "");
	tools::print_av_option_int(context, "qp_p", "        P-Frame", "");
	if (std::string_view("amf_h264") == codec->name) { // B-Frames
		tools::print_av_option_int(context, "qp_b", "        B-Frame", "");

		tools::print_av_option_int(context, "bf", "    B-Frames", "Frames");
		tools::print_av_option_int(context, "bf_delta_qp", "      Delta QP", "");
		tools::print_av_option_bool(context, "bf_ref", "      References");
		tools::print_av_option_int(context, "bf_ref_delta_qp", "        Delta QP", "");
	}

	DLOG_INFO("[%s]     Other:", codec->name);
	tools::print_av_option_int(context, "refs", "      Reference Frames", "Frames");
	tools::print_av_option_bool(context, "enforce_hrd", "      Enforce HRD");
	tools::print_av_option_bool(context, "vbaq", "      VBAQ");
	tools::print_av_option_bool(context, "aud", "      Access Unit Delimiter");
	tools::print_av_option_int(context, "max_au_size", "        Maximum Size", "");
	tools::print_av_option_bool(context, "me_half_pel", "      Half-Pel Motion Estimation");
	tools::print_av_option_bool(context, "me_quarter_pel", "      Quarter-Pel Motion Estimation");
}

// H264 Handler
//--------------

amf_h264::amf_h264() : handler("h264_amf") {}

amf_h264::~amf_h264() {}

bool amf_h264::has_keyframes(ffmpeg_factory* instance)
{
	return true;
}

bool amf_h264::is_hardware(ffmpeg_factory* instance)
{
	return true;
}

bool amf_h264::has_threading(ffmpeg_factory* instance)
{
	return false;
}

void streamfx::encoder::ffmpeg::amf_h264::adjust_info(ffmpeg_factory* factory, std::string& id, std::string& name, std::string& codec)
{
	name = "AMD AMF H.264/AVC (via FFmpeg)";
	if (!amf::is_available())
		factory->get_info()->caps |= OBS_ENCODER_CAP_DEPRECATED;
	factory->get_info()->caps |= OBS_ENCODER_CAP_DEPRECATED;
}

void amf_h264::defaults(ffmpeg_factory* factory, obs_data_t* settings)
{
	amf::defaults(factory, settings);

	obs_data_set_default_int(settings, ST_KEY_H264_PROFILE, static_cast<int64_t>(h264::profile::HIGH));
	obs_data_set_default_int(settings, ST_KEY_H264_LEVEL, static_cast<int64_t>(h264::level::UNKNOWN));
}

void amf_h264::properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	if (!instance) {
		this->get_encoder_properties(factory, instance, props);
	} else {
		this->get_runtime_properties(factory, instance, props);
	}
}

void amf_h264::migrate(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, uint64_t version)
{
	amf::migrate(factory, instance, settings, version);
}

void amf_h264::update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	auto codec   = factory->get_avcodec();
	auto context = instance->get_avcodeccontext();

	amf::update(factory, instance, settings);

	{
		auto found = h264_profiles.find(static_cast<h264::profile>(obs_data_get_int(settings, ST_KEY_H264_PROFILE)));
		if (found != h264_profiles.end()) {
			av_opt_set(context->priv_data, "profile", found->second.c_str(), 0);
		}
	}

	{
		auto found = h264_levels.find(static_cast<h264::level>(obs_data_get_int(settings, ST_KEY_H264_LEVEL)));
		if (found != h264_levels.end()) {
			av_opt_set(context->priv_data, "level", found->second.c_str(), 0);
		} else {
			av_opt_set(context->priv_data, "level", "auto", 0);
		}
	}
}

void amf_h264::override_update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	amf::override_update(factory, instance, settings);
}

void amf_h264::log(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	auto codec   = factory->get_avcodec();
	auto context = instance->get_avcodeccontext();

	amf::log(factory, instance, settings);

	DLOG_INFO("[%s]     H.264/AVC:", codec->name);
	::streamfx::ffmpeg::tools::print_av_option_string2(context, context->priv_data, "profile", "      Profile", [](int64_t v, std::string_view o) { return std::string(o); });
	::streamfx::ffmpeg::tools::print_av_option_string2(context, context->priv_data, "level", "      Level", [](int64_t v, std::string_view o) { return std::string(o); });
}

void amf_h264::get_encoder_properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	amf::properties_before(factory, instance, props);

	{
		obs_properties_t* grp = obs_properties_create();
		obs_properties_add_group(props, S_CODEC_H264, D_TRANSLATE(S_CODEC_H264), OBS_GROUP_NORMAL, grp);

		{
			auto p = obs_properties_add_list(grp, ST_KEY_H264_PROFILE, D_TRANSLATE(S_CODEC_H264_PROFILE), OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
			obs_property_list_add_int(p, D_TRANSLATE(S_STATE_DEFAULT), static_cast<int64_t>(h264::profile::UNKNOWN));
			for (auto const kv : h264_profiles) {
				std::string trans = std::string(S_CODEC_H264_PROFILE) + "." + kv.second;
				obs_property_list_add_int(p, D_TRANSLATE(trans.c_str()), static_cast<int64_t>(kv.first));
			}
		}
		{
			auto p = obs_properties_add_list(grp, ST_KEY_H264_LEVEL, D_TRANSLATE(S_CODEC_H264_LEVEL), OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
			obs_property_list_add_int(p, D_TRANSLATE(S_STATE_AUTOMATIC), static_cast<int64_t>(h264::level::UNKNOWN));
			for (auto const kv : h264_levels) {
				obs_property_list_add_int(p, kv.second.c_str(), static_cast<int64_t>(kv.first));
			}
		}
	}

	amf::properties_after(factory, instance, props);
}

void amf_h264::get_runtime_properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	amf::properties_runtime(factory, instance, props);
}

void amf_h264::override_colorformat(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, AVPixelFormat& target_format)
{
	target_format = AV_PIX_FMT_NV12;
}

static auto inst_h264 = amf_h264();

// H265/HEVC Handler
//-------------------

amf_hevc::amf_hevc() : handler("hevc_amf") {}

amf_hevc::~amf_hevc(){};

bool amf_hevc::has_keyframes(ffmpeg_factory* instance)
{
	return true;
}

bool amf_hevc::is_hardware(ffmpeg_factory* instance)
{
	return true;
}

bool amf_hevc::has_threading(ffmpeg_factory* instance)
{
	return false;
}

void streamfx::encoder::ffmpeg::amf_hevc::adjust_info(ffmpeg_factory* factory, std::string& id, std::string& name, std::string& codec)
{
	name = "AMD AMF H.265/HEVC (via FFmpeg)";
	if (!amf::is_available())
		factory->get_info()->caps |= OBS_ENCODER_CAP_DEPRECATED;
	factory->get_info()->caps |= OBS_ENCODER_CAP_DEPRECATED;
}

void amf_hevc::defaults(ffmpeg_factory* factory, obs_data_t* settings)
{
	amf::defaults(factory, settings);

	obs_data_set_default_int(settings, ST_KEY_HEVC_PROFILE, static_cast<int64_t>(hevc::profile::MAIN));
	obs_data_set_default_int(settings, ST_KEY_HEVC_TIER, static_cast<int64_t>(hevc::profile::MAIN));
	obs_data_set_default_int(settings, ST_KEY_HEVC_LEVEL, static_cast<int64_t>(hevc::level::UNKNOWN));
}

void amf_hevc::properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	if (!instance) {
		this->get_encoder_properties(factory, instance, props);
	} else {
		this->get_runtime_properties(factory, instance, props);
	}
}

void amf_hevc::migrate(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, uint64_t version)
{
	amf::migrate(factory, instance, settings, version);
}

void amf_hevc::update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	auto codec   = factory->get_avcodec();
	auto context = instance->get_avcodeccontext();

	amf::update(factory, instance, settings);

	{ // HEVC Options
		auto found = hevc_profiles.find(static_cast<hevc::profile>(obs_data_get_int(settings, ST_KEY_HEVC_PROFILE)));
		if (found != hevc_profiles.end()) {
			av_opt_set(context->priv_data, "profile", found->second.c_str(), 0);
		}
	}
	{
		auto found = hevc_tiers.find(static_cast<hevc::tier>(obs_data_get_int(settings, ST_KEY_HEVC_TIER)));
		if (found != hevc_tiers.end()) {
			av_opt_set(context->priv_data, "tier", found->second.c_str(), 0);
		}
	}
	{
		auto found = hevc_levels.find(static_cast<hevc::level>(obs_data_get_int(settings, ST_KEY_HEVC_LEVEL)));
		if (found != hevc_levels.end()) {
			av_opt_set(context->priv_data, "level", found->second.c_str(), 0);
		} else {
			av_opt_set(context->priv_data, "level", "auto", 0);
		}
	}
}

void amf_hevc::override_update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	amf::override_update(factory, instance, settings);
}

void amf_hevc::log(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	auto codec   = factory->get_avcodec();
	auto context = instance->get_avcodeccontext();

	amf::log(factory, instance, settings);

	DLOG_INFO("[%s]     H.265/HEVC:", codec->name);
	::streamfx::ffmpeg::tools::print_av_option_string2(context, "profile", "      Profile", [](int64_t v, std::string_view o) { return std::string(o); });
	::streamfx::ffmpeg::tools::print_av_option_string2(context, "level", "      Level", [](int64_t v, std::string_view o) { return std::string(o); });
	::streamfx::ffmpeg::tools::print_av_option_string2(context, "tier", "      Tier", [](int64_t v, std::string_view o) { return std::string(o); });
}

void amf_hevc::get_encoder_properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	amf::properties_before(factory, instance, props);

	{
		obs_properties_t* grp = obs_properties_create();
		obs_properties_add_group(props, S_CODEC_HEVC, D_TRANSLATE(S_CODEC_HEVC), OBS_GROUP_NORMAL, grp);

		{
			auto p = obs_properties_add_list(grp, ST_KEY_HEVC_PROFILE, D_TRANSLATE(S_CODEC_HEVC_PROFILE), OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
			obs_property_list_add_int(p, D_TRANSLATE(S_STATE_DEFAULT), static_cast<int64_t>(hevc::profile::UNKNOWN));
			for (auto const kv : hevc_profiles) {
				std::string trans = std::string(S_CODEC_HEVC_PROFILE) + "." + kv.second;
				obs_property_list_add_int(p, D_TRANSLATE(trans.c_str()), static_cast<int64_t>(kv.first));
			}
		}
		{
			auto p = obs_properties_add_list(grp, ST_KEY_HEVC_TIER, D_TRANSLATE(S_CODEC_HEVC_TIER), OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
			obs_property_list_add_int(p, D_TRANSLATE(S_STATE_DEFAULT), static_cast<int64_t>(hevc::tier::UNKNOWN));
			for (auto const kv : hevc_tiers) {
				std::string trans = std::string(S_CODEC_HEVC_TIER) + "." + kv.second;
				obs_property_list_add_int(p, D_TRANSLATE(trans.c_str()), static_cast<int64_t>(kv.first));
			}
		}
		{
			auto p = obs_properties_add_list(grp, ST_KEY_HEVC_LEVEL, D_TRANSLATE(S_CODEC_HEVC_LEVEL), OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
			obs_property_list_add_int(p, D_TRANSLATE(S_STATE_AUTOMATIC), static_cast<int64_t>(hevc::level::UNKNOWN));
			for (auto const kv : hevc_levels) {
				obs_property_list_add_int(p, kv.second.c_str(), static_cast<int64_t>(kv.first));
			}
		}
	}

	amf::properties_after(factory, instance, props);
}

void amf_hevc::get_runtime_properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	amf::properties_runtime(factory, instance, props);
}

static auto inst_hevc = amf_hevc();
