#include <string>
#include <string_view>
#include <ztd/text/decode.hpp>
#include <ztd/text/encode.hpp>
#include <ztd/text/validate_transcodable_as.hpp>
#include <ztd/text/encoding.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
    if (Size > 0) {
        uint8_t opt = Data[0];
        auto strView = std::string_view((char*)Data+1, Size-1);
        switch (opt) {
            case 0:
                ztd::text::decode_to(strView, ztd::text::utf8);
                break;
            case 1:
                ztd::text::decode_to(strView, ztd::text::utf16);
                break;
            case 2:
                ztd::text::decode_to(strView, ztd::text::utf32);
                break;
            case 3:
                ztd::text::encode_to(strView, ztd::text::utf8);
                break;
            case 4:
                ztd::text::encode_to(strView, ztd::text::utf16);
                break;
            case 5:
                ztd::text::encode_to(strView, ztd::text::utf32);
                break;
            case 6:
                ztd::text::validate_transcodable_as(strView, ztd::text::utf8, ztd::text::utf16);
                break;
            case 7:
                ztd::text::validate_transcodable_as(strView, ztd::text::utf8, ztd::text::utf32);
                break;
            case 8:
                ztd::text::validate_transcodable_as(strView, ztd::text::utf16, ztd::text::utf8);
                break;
            case 9:
                ztd::text::validate_transcodable_as(strView, ztd::text::utf16, ztd::text::utf32);
                break;
            case 10:
                ztd::text::validate_transcodable_as(strView, ztd::text::utf32, ztd::text::utf8);
                break;
            case 11:
                ztd::text::validate_transcodable_as(strView, ztd::text::utf32, ztd::text::utf16);
                break;
        }
    }
	return 0;
}