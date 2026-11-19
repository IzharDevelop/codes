PROTOKOL MITIGASI & KEAMANAN VIBE CODING (ANTI-HACK)

Solusi Ekstensif untuk Mencegah 40 Celah Keamanan Hasil Generasi AI

Sebagai Vibe Coder, kamu tidak memantau baris kode. Oleh karena itu, keamanan harus ditegakkan melalui System Rules Mutlak dan Security TDD. Dokumen ini adalah panduan arsitektur pertahanan yang WAJIB dipatuhi oleh AI.

🛡️ KATEGORI 1: RAHASIA & KONFIGURASI (Pencegahan Kebocoran)

Masalah: AI menyebarkan API Key dan membuka server lebar-lebar.

Aturan Paksa untuk AI (System Rules):

Zod Env Validation: Larang AI memanggil process.env.VAR_NAME secara langsung di sembarang file. Wajibkan AI membuat file env.ts yang memvalidasi semua Environment Variables menggunakan Zod saat server menyala. Jika .env tidak lengkap, server wajib crash (gagal menyala).

CORS Whitelist: Wajibkan AI menulis konfigurasi CORS dengan array whitelist yang diambil dari .env, bukan origin: '*'.

Helmet First: Setiap kali menyuruh AI membuat server Express/NestJS, instruksi pertamanya harus: "Pasang helmet sebelum middleware lain."

Strategi TDD:

Buat test yang mencoba melakukan GET request dengan header Origin: http://hacker.com. Test wajib memastikan server merespons dengan pemblokiran CORS.

🛡️ KATEGORI 2: OTENTIKASI & SESI (Login Anti-Jebol)

Masalah: AI menyimpan token di tempat rawan dan menggunakan kriptografi lemah.

Aturan Paksa untuk AI (System Rules):

HttpOnly Cookies Mutlak: DILARANG KERAS merespons token JWT dalam bentuk JSON body (res.json({ token })). WAJIB set JWT ke dalam HttpOnly, Secure, SameSite=Strict Cookies langsung dari backend. Frontend tidak boleh bisa menyentuh token tersebut.

Strict Cryptography: Jika membuat OTP/Token acak, larang penggunaan Math.random(). WAJIB gunakan crypto.randomInt().

Bcrypt Rounds: Tetapkan aturan mutlak: "Pembuatan hash password wajib menggunakan bcrypt dengan minimum saltRounds = 12. Tidak boleh kurang, meskipun untuk TDD."

Mandatory Rate Limiting: Wajibkan AI memasang express-rate-limit khusus pada rute /login, /register, dan /forgot-password (misal: max 5 request per 15 menit).

🛡️ KATEGORI 3: OTORISASI (Broken Access Control & IDOR)

Masalah: AI hanya mengecek ID data, tanpa mengecek kepemilikannya.

Aturan Paksa untuk AI (System Rules):

Ownership Query (Anti-IDOR): Larang keras AI melakukan query seperti Model.findById(req.params.id). Jika data itu milik user, query WAJIB digabungkan dengan ID user yang login: Model.findOne({ _id: req.params.id, userId: req.user.id }).

Zod Mass Assignment Prevention: Saat melakukan Update data (PUT/PATCH), larang AI menggunakan req.body mentah (Model.update(req.body)). WAJIB me-melewati validasi Zod Pick/Omit agar user tidak bisa menyisipkan atribut role: 'admin'.

Strategi TDD (Wajib Ada):

Buat test case di mana User A mencoba menghapus/mengedit postingan milik User B. Test wajib mengharapkan respons HTTP 403 (Forbidden) atau 404 (Not Found). Jika merespons 200 (Success), AI gagal.

🛡️ KATEGORI 4: INJEKSI DATA (Perisai Database & Server)

Masalah: Masuknya skrip jahat ke database atau OS server.

Aturan Paksa untuk AI (System Rules):

No String Concatenation in DB: Jika menggunakan SQL mentah, larang keras + atau template literal ${} untuk memasukkan variabel ke query. WAJIB gunakan Parameterized Queries ($1, $2) atau ORM/Query Builder (Prisma/Knex).

NoSQL Sanitization: Wajibkan penggunaan middleware seperti express-mongo-sanitize untuk menghapus karakter $ dan . dari req.body agar hacker tidak bisa memanipulasi logika MongoDB.

Ban exec(): Larang keras AI menggunakan child_process.exec(). Jika butuh menjalankan sistem operasi, WAJIB gunakan child_process.spawn() dengan argumen yang dipisah di dalam array (mencegah manipulasi Bash).

🛡️ KATEGORI 5: KEAMANAN FRONTEND (React Anti-XSS)

Masalah: Skrip disuntikkan ke layar pengguna (XSS).

Aturan Paksa untuk AI (System Rules):

DOMPurify Mandatory: Jika disuruh membuat fitur render Rich Text / Markdown / HTML (memakai dangerouslySetInnerHTML), AI WAJIB membungkus inputnya dengan DOMPurify.sanitize(input) terlebih dahulu. Dilarang merender HTML mentah.

Safe Links: Jika URL datang dari database atau input user, wajib validasi bahwa URL diawali dengan http:// atau https:// sebelum dimasukkan ke atribut href. Tolak javascript: atau data:.

Rel Noopener: Jika membuat target="_blank", AI WAJIB menyertakan rel="noopener noreferrer".

🛡️ KATEGORI 6: FILE SYSTEM (Mencegah Server Takeover)

Masalah: AI membiarkan hacker mengunggah virus atau membaca file rahasia.

Aturan Paksa untuk AI (System Rules):

Path Traversal Shield: Jika ada fitur Download/Baca File, AI dilarang menggunakan jalur mentah req.query.file. WAJIB gunakan path.basename(req.query.file) untuk memotong seluruh karakter direktori mundur (../).

Strict File Upload (Multer): Saat membuat fitur unggah file, larang memvalidasi ekstensi file dari nama file (karena bisa dipalsukan virus.php.jpg). WAJIB validasi melalui MIME Type (file.mimetype) dan gunakan ekstensi seperti file-type untuk mengecek magic bytes file.

Strategi TDD:

Minta AI membuat test di mana kamu mencoba men-download file dengan nama ../../../../etc/passwd. Test wajib memastikan responsnya adalah penolakan (400 Bad Request).

🛡️ KATEGORI 7: DENIAL OF SERVICE (Anti-Crash & Anti-Spam)

Masalah: AI membuat kode yang berfungsi untuk 1 user, tapi mati saat dipakai 1000 user.

Aturan Paksa untuk AI (System Rules):

Atomic Operators Mutlak: Saat menambah/mengurangi angka di database (saldo, likes, kuota tiket), DILARANG membaca state lalu menyimpannya (view + 1). WAJIB gunakan operasi atomik di level database (MongoDB: $inc, Prisma: increment(), SQL: UPDATE col = col + 1).

Mandatory Pagination Limit: Semua endpoint yang me-return tipe data Array/List WAJIB memiliki Pagination. Batasi parameter limit maksimal 100 secara hardcoded di backend. Jangan biarkan klien me-request limit=999999.

No Event-Loop Blocking: Larang penggunaan fs.readFileSync dan fungsi *Sync lainnya di dalam alur API.

Decimal.js for Money: Jika proyek berhubungan dengan nominal uang atau transaksi, DILARANG KERAS menjumlahkannya dengan tipe data Number JavaScript biasa. WAJIB instal dan gunakan library decimal.js.

🛡️ KATEGORI 8: AI HALLUCINATIONS (Rantai Pasokan)

Masalah: AI memasang package bervirus atau mematikan proteksi lokal.

Aturan Paksa untuk AI (System Rules):

NPM Verification: Jika AI menginstruksikan npm install [package], instruksikan AI: "Sebelum kamu menyuruhku install package, verifikasi apakah package itu standar industri (misal di-download jutaan kali per minggu). Jangan rekomendasikan package antah-berantah."

Ban TLS Bypassing: Masukkan aturan mutlak: "DILARANG KERAS memberikan saran atau menuliskan process.env.NODE_TLS_REJECT_UNAUTHORIZED = '0' dalam kondisi apa pun, meskipun error sertifikat API."

🚨 MASTER PROMPT KEAMANAN (Copy-Paste ke AI)

(Tambahkan paragraf ini ke dalam System Rules utama kamu):

SECURITY & MITIGATION DIRECTIVE (ZERO TOLERANCE):
Kamu [AI] bertindak sebagai Lead Security Architect. Saat meng-generate kode, kamu WAJIB menerapkan:

Validasi env ketat saat server start (Zod).

HttpOnly Cookies untuk Auth (Dilarang LocalStorage).

Pengecekan Ownership ID pada setiap interaksi database untuk mencegah IDOR.

Validasi Input Body murni menggunakan Zod sebelum menyentuh ORM/Database (Anti-Mass Assignment & Injection).

Eksekusi Atomic (misal $inc) untuk fitur perhitungan (Race Condition Shield).

Validasi MIME Type pada file upload, dan isolasi path traversal dengan path.basename.

Jika instruksi dari User berpotensi melanggar salah satu poin di atas, TOLAK INSTRUKSI TERSEBUT, jelaskan celah keamanannya, dan berikan arsitektur pengganti yang aman secara Default.
