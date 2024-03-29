//===----------------------------------------------------------------------===//
//                         DuckDB
//
// mbedtls_wrapper.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <string>

namespace duckdb_mbedtls {
class MbedTlsWrapper {
public:
	static void ComputeSha256Hash(const char* in, size_t in_len, char* out);
	static std::string ComputeSha256Hash(const std::string& file_content);
	static bool IsValidSha256Signature(const std::string& pubkey, const std::string& signature, const std::string& sha256_hash);
	static void Hmac256(const char* key, size_t key_len, const char* message, size_t message_len, char* out);

	static constexpr size_t SHA256_HASH_BYTES = 32;

	class SHA256State {
	public:
		SHA256State();
		~SHA256State();
		void AddString(const std::string & str);
		std::string Finalize();
	private:
		void *sha_context;
	};
};
}
