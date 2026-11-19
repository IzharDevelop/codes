# Standar Operasional AI Coding (Wajib Ikut)

Dokumen ini adalah pedoman kerja resmi untuk AI yang mengerjakan project ini.
Tujuan utamanya: hasil kerja konsisten, aman, fokus, minim regresi, dan mudah diaudit.

---

## A. Aturan Emas (Tidak Boleh Dilanggar)

1. **Single Task Focus**
- AI wajib fokus **1 task utama** sesuai perintah user.
- AI **dilarang** mengerjakan task lain yang tidak diminta.
- AI **dilarang** mengubah modul/fitur yang tidak berhubungan langsung.

2. **No Side Effect**
- AI tidak boleh menyebabkan perubahan perilaku fitur lain.
- Jika ada kebutuhan teknis yang memaksa menyentuh area lain:
  - wajib konfirmasi dulu ke user (jelaskan alasan + risiko),
  - setelah perubahan, wajib bukti bahwa fungsi lama tetap normal.

3. **No Silent Change**
- Tidak boleh ada perubahan “diam-diam” yang tidak dilaporkan.
- Semua file yang berubah harus dicatat di `report.md`.

4. **No Unverified Claim**
- AI dilarang bilang “sudah aman” tanpa verifikasi.
- Setiap klaim fix wajib disertai test/check yang relevan.

---

## B. Cara Kerja Wajib: SDLC + TDD

## B1) SDLC (Software Development Life Cycle)

AI wajib mengikuti urutan ini:

1. **Requirement Lock**
- Ringkas permintaan user dalam 1 scope utama.
- Definisikan in-scope dan out-of-scope.
- Jika ada ambiguitas kritis, tanyakan 1 klarifikasi spesifik.

2. **Impact Analysis**
- Petakan file/modul yang terdampak langsung.
- Tulis risiko regresi paling mungkin.
- Tentukan batas perubahan (change boundary).

3. **Plan**
- Buat rencana implementasi bertahap.
- Jika diminta user, tulis di `planning.md` format dropdown `<details>`.

4. **Implementation**
- Implementasi kecil bertahap.
- Hindari refactor besar di luar kebutuhan task.

5. **Verification**
- Jalankan test target.
- Jalankan regression test area berdekatan.
- Jalankan build/check bila relevan.

6. **Report & Handover**
- Update `report.md`:
  - ringkasan perubahan,
  - daftar file berubah,
  - bukti test,
  - risiko tersisa (jika ada).

## B2) TDD (Red -> Green -> Refactor)

1. **Red**
- Tulis test yang mereproduksi bug / ekspektasi fitur baru.
- Pastikan test gagal lebih dulu.

2. **Green**
- Tulis perubahan minimal agar test lulus.
- Jangan menambah perubahan di luar kebutuhan test.

3. **Refactor**
- Rapikan code yang perlu, tanpa ubah behavior.
- Retest untuk pastikan tetap hijau.

---

## C. Protokol Fokus Task (Sangat Penting)

Setiap awal kerja AI wajib menetapkan:
- **Task Aktif**: satu kalimat.
- **Batas Scope**: file/fitur apa saja yang boleh disentuh.
- **Larangan**: area yang tidak boleh diubah.

Contoh:
- Task Aktif: “Fix uploader DOCX ke JSON soal.”
- Batas Scope: `routes/uploads`, parser helper, test uploader.
- Larangan: auth, maintenance, chat, dashboard UI.

### Jika Harus Menyentuh Area Lain
AI wajib lakukan urutan ini:
1. Berhenti dulu.
2. Jelaskan ke user:
   - kenapa area lain perlu disentuh,
   - dampaknya apa,
   - cara memastikan fitur lama tetap normal.
3. Tunggu persetujuan user.
4. Setelah implementasi:
   - jalankan regresi area terdampak,
   - laporkan hasil validasi.

---

## D. Aturan Perubahan Kode

1. Ubah sekecil mungkin (minimal diff).
2. Utamakan kompatibilitas backward.
3. Jangan ubah kontrak API/UI tanpa persetujuan.
4. Jangan hapus fitur existing kecuali diminta.
5. Jangan menambah dependency baru tanpa alasan kuat.
6. Komentar kode hanya untuk logika kompleks, tidak berlebihan.

---

## E. Aturan Debugging

Saat user minta debug:

1. Reproduksi error.
2. Identifikasi akar masalah (root cause), bukan gejala saja.
3. Klasifikasikan error:
- `BUG_LOGIC`
- `CONFIG_ENV`
- `DATA_ISSUE`
- `EXTERNAL_API`
- `PERMISSION_AUTH`
- `PERFORMANCE`

4. Perbaiki berdasarkan prioritas dampak.
5. Buat daftar di `error.md`:
- Error
- Lokasi
- Akar masalah
- Dampak
- Fix
- Status verifikasi

---

## F. Aturan Testing Minimum

Setiap task wajib minimal:
- test area yang diubah,
- regression test area terdekat,
- build/type-check (jika frontend/backend terkena).

Checklist:
- [ ] Test baru untuk bug/fitur ini
- [ ] Test existing terkait masih lulus
- [ ] Build/check lulus
- [ ] Tidak ada error runtime baru pada scope

Jika ada test yang tidak bisa dijalankan:
- tulis jujur alasannya,
- tulis risiko yang tersisa.

---

## G. Aturan Keamanan

1. Dilarang expose secret/API key.
2. Validasi input (server-side wajib).
3. Sanitasi output yang dirender.
4. Kunci upload MIME/ukuran/path traversal.
5. Lindungi session/token (no leakage di log/report).
6. Error message ke user jangan bocorkan detail sensitif.

---

## H. Aturan Performa & Skalabilitas

1. Jangan menambah query/network call yang tidak perlu.
2. Gunakan cache/throttle/debounce bila relevan.
3. Hindari loop berat di request path kritis.
4. Jika optimasi besar berdampak arsitektur, minta persetujuan user dulu.

---

## I. Aturan Dokumentasi Wajib

## I1) `report.md` (wajib tiap update)
Wajib berisi:
- tanggal/jam,
- ringkasan task,
- langkah SDLC ringkas,
- bukti TDD (Red/Green/Refactor),
- file yang diubah,
- hasil test,
- risiko/next step.

## I2) `planning.md` (saat user minta planning)
Gunakan format dropdown:
- `<details><summary>Status Fix</summary>...</details>`
- `<details><summary>Bug/Gap Ditemukan</summary>...</details>`
- `<details><summary>Rencana Debug & Perbaikan</summary>...</details>`
- `<details><summary>Checklist TDD</summary>...</details>`

## I3) `error.md` (saat user minta debug list)
Gunakan format tabel/list terstruktur agar mudah audit.

---

## J. Aturan Backup (On-Demand)

Backup hanya jalan jika user menulis: **“backup datanya”**.

Prosedur:
1. Zip `cms-ujian` dan `cms-ujian-backend`.
2. `node_modules` tidak ikut.
3. File `.env` tetap ikut backup.
4. Simpan ke `sampah/backup`.
5. Nama zip format: `DD-MM-YYYY.zip`.

---

## K. Format Konfirmasi Wajib (Saat Perlu Ubah Area Lain)

AI wajib kirim format ini ke user:

1. Alasan teknis kenapa area lain harus diubah.
2. File yang akan terdampak.
3. Risiko jika tidak diubah.
4. Cara validasi pasca perubahan.
5. Minta persetujuan eksplisit sebelum lanjut.

---

## L. Definition of Done (DoD)

Task dianggap selesai hanya jika semua terpenuhi:
- Scope utama selesai sesuai perintah.
- Tidak ada perubahan liar di luar scope.
- Test relevan lulus.
- Regression area terkait lulus.
- Build/check lulus (jika relevan).
- `report.md` diperbarui.
- Jika diminta: `error.md` / `planning.md` juga diperbarui.

---

## M. Mode Perilaku AI Saat Eksekusi

1. Komunikasi singkat, jelas, berbasis bukti.
2. Proaktif, tapi tidak melebar dari task aktif.
3. Jika ragu, pilih opsi paling aman terhadap fitur existing.
4. Jangan pernah “mengorbankan” stabilitas demi cepat selesai.

Dokumen ini wajib dijadikan template default setiap kali AI melakukan coding/update di project ini.