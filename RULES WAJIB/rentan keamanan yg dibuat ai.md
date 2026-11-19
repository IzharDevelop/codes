DAFTAR EKSTENSIF: 40 CELAH KEAMANAN (VULNERABILITIES) HASIL KODE AI

Buku Putih Keamanan Vibe Coding untuk React & Node.js

AI (LLM) dilatih untuk "membuat program berjalan", BUKAN "membuat program aman". Dokumen ini membedah 40 jalan pintas berbahaya yang sering diambil AI, yang bisa membuat aplikasimu diretas, database-mu dicuri, atau servermu lumpuh.

🟢 KATEGORI 1: KEBOCORAN RAHASIA & KONFIGURASI

Celah akibat kemalasan AI dalam mengatur environment.

Hardcoded Secrets: AI menulis const apiKey = 'sk-123...' langsung di dalam file komponen atau controller. Jika ter-push ke GitHub, tamat.

Wildcard CORS (origin: '*'): AI membuka pintu API untuk diakses oleh domain mana pun di seluruh dunia karena malas men-setting domain spesifik.

Verbose Error Boundaries: AI merespons res.status(500).json({ error: err.stack }). Ini memberikan peta struktur folder server dan versi database kepada hacker.

Exposing Env Vars to Frontend: Di React/Next.js, AI sering memasukkan API Key internal ke dalam konfigurasi klien (NEXT_PUBLIC_DB_PASSWORD), membuatnya bisa dibaca oleh siapa saja via Inspect Element.

No Security Headers: AI tidak pernah berinisiatif memasang Helmet.js di Express, membuat aplikasi rentan terhadap serangan Clickjacking dan MIME-sniffing.

Leaving Debug Endpoints Open: AI sering membuat rute /api/test-db atau /api/clear-users saat TDD, tapi lupa menghapusnya saat kode di-deploy ke produksi.

🟡 KATEGORI 2: OTENTIKASI (LOGIN) & SESI

Celah saat AI membuat sistem Login/Register.

JWT di LocalStorage: AI sangat sering menyuruh React menyimpan token JWT di localStorage. Ini adalah target utama pencurian token via serangan XSS. (Wajib pakai HttpOnly Cookies).

No JWT Expiration: AI membuat token JWT jwt.sign({ userId }, secret) tanpa parameter expiresIn. Jika token dicuri, hacker bisa memakainya selamanya.

Weak JWT Secret: Dalam TDD, AI sering menggunakan 'secret123' atau 'my-secret-key' dan lupa memberitahumu untuk menggantinya di produksi.

Insecure Randomness (OTP/Token): Saat disuruh membuat kode OTP 6 digit, AI menggunakan Math.random(). Angka ini bisa diprediksi oleh hacker. (Wajib pakai crypto.randomInt()).

No Password Salting: AI menggunakan hash MD5/SHA1, atau menggunakan bcrypt tapi dengan salt rounds yang sangat rendah (misal: 1 atau 2) demi performa TDD.

Missing Rate Limiting: AI membuat form login tanpa Rate Limit. Hacker bisa melakukan Brute Force (mencoba password 100.000 kali per detik) menggunakan bot.

Session Fixation: AI tidak mereset Session ID lama setelah pengguna berhasil login.

🟠 KATEGORI 3: OTORISASI & KONTROL AKSES (Broken Access Control)

Kode berjalan lancar, tapi AI lupa mengecek "Siapa yang me-request?".

IDOR (Insecure Direct Object Reference): Endpoint GET /api/messages/:id. AI hanya mencari pesan dari database berdasarkan ID, TANPA mengecek apakah user yang login adalah pemilik asli pesan tersebut.

Mass Assignment (Over-Posting): AI menulis User.findByIdAndUpdate(req.user.id, req.body). Jika hacker menyisipkan {"role": "admin", "saldo": 99999} di request, sistem akan menerimanya bulat-bulat.

Missing Role Verification: AI membuat TDD yang mengecek apakah user sudah login (punya token), tapi lupa mengecek apakah role user tersebut adalah 'Admin' sebelum mengeksekusi aksi hapus data.

Client-Side Authorization: Di React, AI menyembunyikan tombol "Delete" dengan if (user.isAdmin). TAPI, di backend Node.js, rute /api/delete tidak diproteksi. Hacker bisa menembak rute itu langsung via Postman.

🔴 KATEGORI 4: INJEKSI DATA (The Database Killers)

AI gagal memvalidasi atau membersihkan racun dari input pengguna.

SQL Injection: AI menyambung string langsung: db.query("SELECT * FROM users WHERE username = '" + req.body.username + "'").

NoSQL Injection (MongoDB): AI melemparkan req.body langsung ke Mongoose: User.find({ username: req.body.username }). Hacker bisa mengirim JSON {"username": {"$ne": null}} untuk login tanpa password.

Command Injection (RCE): AI membuat fitur Ping IP atau Resize Gambar menggunakan child_process.exec(). Hacker menyisipkan 8.8.8.8 && rm -rf / untuk menghapus servermu.

Prototype Pollution: Saat membuat fitur "Update Profil", AI menggunakan fungsi Object.assign() atau Deep Merge bawaan tanpa filter, memungkinkan hacker memanipulasi prototype objek global JavaScript.

🟣 KATEGORI 5: KERENTANAN KHUSUS FRONTEND (REACT/UI)

Celah yang membuat browser pengunjungmu diretas.

XSS via dangerouslySetInnerHTML: AI diminta merender Markdown/Rich Text dan langsung memasukkannya ke React tanpa library DOMPurify.

XSS via href Attributes: AI membuat link dari database <a href={user.website}>. Jika user memasukkan javascript:alert('Hacked'), skrip akan jalan saat link diklik.

Reverse Tabnabbing: AI membuat link eksternal target="_blank" tapi lupa menambahkan rel="noopener noreferrer". Web tujuan bisa membajak tab aplikasimu.

Sensitive PII in React State/Redux: AI menyimpan data sensitif (password, NIK, kartu kredit utuh) di global state, yang bisa diekstrak dengan mudah via React DevTools.

🟤 KATEGORI 6: FILE SYSTEM & JARINGAN (Server Takeover)

AI bermain dengan file system tanpa pengaman.

Path Traversal (LFI): Fitur baca file lokal: res.sendFile('/uploads/' + req.query.file). Hacker memasukkan file=../../../.env untuk mencuri API Key.

Unrestricted File Upload: AI lupa memfilter ekstensi. Hacker mengunggah shell.php atau virus.js yang kemudian tereksekusi di server.

Zip Slip (Archive Extraction): Fitur ekstrak ZIP otomatis. AI tidak mengecek apakah isi file ZIP mengandung direktori mundur (../), menimpa file sistem Node.js-mu.

SSRF (Server-Side Request Forgery): Fitur "Ambil gambar dari URL luar". AI menggunakan axios.get(req.body.url). Hacker memasukkan URL internal http://localhost:27017 untuk membobol database dari dalam.

⚫ KATEGORI 7: DENIAL OF SERVICE (DoS) & LOGIKA BISNIS

AI menulis kode yang berfungsi, tapi sangat rapuh jika diserang massal.

Race Conditions (Double Spending): AI mengecek saldo -> kurangi saldo -> simpan (3 langkah terpisah). Jika ditekan 100x dalam 1 milidetik, sistem jebol. Wajib pakai transaksi ACID / $inc.

ReDoS (RegEx DoS): AI membuat Regular Expression (RegEx) yang sangat kompleks untuk memvalidasi email/password. Hacker mengirim string jebakan yang membuat CPU server 100% stuck mengevaluasi RegEx tersebut.

Memory DoS (Unpaginated Queries): AI menulis Model.find(). Saat data mencapai 1 juta baris, RAM server langsung penuh dan Node.js crash (Out of Memory).

Event Loop Blocking: AI menggunakan bcrypt.hashSync() atau loop for miliaran iterasi di main thread. Seluruh pengunjung web harus antre sampai proses itu selesai.

No Upload Size Limit: AI menggunakan multer tapi lupa men-setting limits: { fileSize }. Hacker mengunggah file gambar kosong berukuran 50 GB hingga hardisk servermu penuh.

Unvalidated Redirects: Fitur ?redirect=url. AI langsung merespons res.redirect(req.query.redirect). Hacker bisa memalsukan link login web-mu untuk memancing user ke web phishing.

Floating Point Math Error: AI menjumlahkan uang dengan Number JS biasa (0.1 + 0.2 = 0.30000000000000004). Dalam sistem akuntansi/crypto, ini celah pencurian fraksional. (Wajib pakai library decimal.js).

⚪ KATEGORI 8: AI HALLUCINATIONS & SUPPLY CHAIN

Celah spesifik karena tabiat AI.

Hallucinated Malware Packages: AI sering menyuruhmu melakukan npm install [nama_package_aneh]. Kadang package itu tidak ada, dan hacker sengaja mendaftarkan nama tersebut di NPM berisi virus (Dependency Confusion).

Outdated Vulnerable Dependencies: AI sering menyuruh TDD menggunakan package usang (contoh: request padahal sudah deprecated) yang memiliki celah keamanan bawaan.

Copy-Pasting Bad StackOverflow: AI mengulangi kode "Workaround" jelek dari forum tahun 2015 yang sudah tidak aman untuk standar keamanan web tahun sekarang.

Bypassing SSL/TLS Certificates: Saat AI gagal memanggil API HTTPS karena error sertifikat lokal, AI menaruh process.env.NODE_TLS_REJECT_UNAUTHORIZED = '0'. Ini mematikan enkripsi HTTPS secara global, membuat aplikasimu rentan disadap (Man-in-the-Middle Attack).
