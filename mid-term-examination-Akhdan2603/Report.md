(im sorry sir i think i accidently create this md on code, so if you on preview mode it will look a mess, i appologize for my carelessness)

1. Analyze and finding correct window size in identifying a segment.
   A. Metodology
     Program mengimplementasikan sliding window untuk mengekstrak semua window 3×3 dari canvas. Setiap window di-dump ke file window_dump.txt untuk analisis.
     for(int i = 1; i < image.width()-1; i++){
        for(int j = 1; j < image.height()-1; j++){
            bool local_window[3][3] = {false};
            // Extract 3x3 neighborhood
            CustomMatrix mat(local_window);
            allWindows.push_back(mat);
        }
      }
   B. Result
     Window Size 3x3 (9 pixels)
     1. hasil
         Current window size: 3x3
        Total windows analyzed: 372504
        Non-empty windows: 73640
        Empty windows: 298864
        Non-empty ratio: 19.7689%
       pada ukuran window 3x3 menunjukkan Non-empty ratio sebesar 19.77%
       ukuran 3x3 sangat efisien dalam mendeteksi fitur edge yang sangat kecil namun dengan Non-empty ratio yang relatif rendah
       menunjukkan bahwa window 3x3 kemungkinan terlalu kecil untuk menangkap keseluruhan segmen sebagai satu kesatuan
3. Report all fitting of appropriate window pattern for identifying a segment.
   A. Detector pattern library
     dengan implementasi menggunakan metode 8 detector pattern untuk menangkap berbagai orientasi line segment
       Pattern set :
       1. Horizontal
           000
           111
           000
         mendeteksi segmen horizontal dengan menggunakan horizontal edges dan table lines
       2. Vertical
           010
           010
           010
         mendeteksi segmen vertikal, dengan menggunakan vertikal edges dan borders
       3. Diagonal 45 derajat
           100
           010
           001
         mendeteksi Top-left to bottom-right diagonal 
      4. Diagonal 135 derajat
           001
           010
           100
         mendeteksi top-right to bottom-left diagonal
     5-8. Partial pattern
         Partial Horizontal:    Partial Vertical:
          0 0 0    0 0 0         0 1 0    0 0 0
          1 1 0    0 1 1         0 1 0    0 1 0
          0 0 0    0 0 0         0 0 0    0 1 0
         mendeteksi line endpoints dan partial segment
   B. Pattern matching Result (based on windows_analysis.txt)

      Pattern: Horizontal Line
      Matches: 0
      Pattern matrix:
      0 0 0 
      1 1 1 
      0 0 0 
      
      Pattern: Vertical Line
      Matches: 0
      Pattern matrix:
      0 1 0 
      0 1 0 
      0 1 0 
      
      Pattern: Diagonal (TL-BR)
      Matches: 1181
      Pattern matrix:
      1 0 0 
      0 1 0 
      0 0 1 
      
      Pattern: Diagonal (TR-BL)
      Matches: 1517
      Pattern matrix:
      0 0 1 
      0 1 0 
      1 0 0 
      
      Pattern: Partial Horizontal 1
      Matches: 619
      Pattern matrix:
      0 0 0 
      1 1 0 
      0 0 0 
      
      Pattern: Partial Horizontal 2
      Matches: 626
      Pattern matrix:
      0 0 0 
      0 1 1 
      0 0 0 
      
      Pattern: Partial Vertical 1
      Matches: 558
      Pattern matrix:
      0 1 0 
      0 1 0 
      0 0 0 
      
      Pattern: Partial Vertical 2
      Matches: 530
      Pattern matrix:
      0 0 0 
      0 1 0 
      0 1 0 

      berdasarkan hasil diatas pola pla berikut saya anggap paling sesuai untuk mendeteksi fragmen segmen
       1. pola diagonal (dominan)
         pola diagonal (TR-BL) dengan 1.517 matches, ini adalah pola yang paling sering ditemui, menunjukkan kemiringan dari TopRight-BottomLeft
         pola diagonal (TL-BR) dengan 1.187 matches, pola ini juga sangat dominan dan menunjukkan struktur kemiringan dari arah sebaliknya
       2. pola garis parsial ( pendukung)
         Pola garis parsial (Horizontal dan Vertikal) juga memberikan jumlah kecocokan yang signifikan (sekitar 500-600 kecocokan).
         Pola-pola ini merepresentasikan:
         - Patahan/Sudut: Pola parsial sering kali menandakan titik akhir (endpoint) dari sebuah garis atau sudut (corner) di mana garis berhenti atau berbelok.
         - Potongan Garis: Dalam konteks 3 X 3, pola ini mendeteksi fragmen-fragmen pendek dari garis horizontal dan vertikal yang belum mencapai panjang penuh 3 X 3
       3. pola tidak sesuai
         Penting untuk dicatat bahwa pola Garis Horizontal Penuh dan Garis Vertikal Penuh memiliki 0 kecocokan.
         Hal ini memperkuat hipotesis bahwa struktur segmen target sangat jarang mengandung garis lurus ortogonal yang stabil setidaknya sepanjang 3 piksel.
         ini mengartikan sistem lebih memprioritaskan fitur diagonal dan fragmen
3. Automated Detection Algorithm
   1. Algorithm Overview
        implementation flow :
        1. ambil Kanvas -> QImage: Tangkap konten visual kanvas (area kerja) dan simpan sebagai objek gambar Qt, yaitu QImage.
        2. Ekstraksi Jendela 3X3: Lakukan proses sliding window (jendela geser) untuk mengekstrak semua jendela berukuran 3X3 dari seluruh QImage yang ditangkap.
        3. Analisis dan Penandaan Kandidat:
             Untuk setiap jendela 3X3 yang tidak kosong (non-empty):
             Bandingkan jendela tersebut dengan 8 pola detektor yang telah ditentukan.
             Jika nilai kesamaan (similarity) lebih besar atau sama dengan 0.66, tandai jendela tersebut sebagai kandidat segmen.
        4. Ekspor Berkas Analisis: Hasil pemrosesan harus dicatat dan diekspor ke dalam dua berkas:
             window_dump.txt: Berisi dump (data mentah) dari semua jendela yang dianalisis.
             window_analysis.txt: Berisi ringkasan hasil perbandingan dan statistik jendela.
        5. Visualisasi Hasil: Tandai lokasi semua kandidat segmen yang terdeteksi dengan menggambar persegi panjang berwarna ungu (purple rectangles) pada kanvas asli.
    2. Core Implementation
         void DrawingCanvas::segmentDetection(){
              QPixmap pixmap = this->grab();
              QImage image = pixmap.toImage();
              allWindows.clear();
              candidatePositions.clear();
              // Sliding window extraction
              for(int i = 1; i < image.width()-1; i++){
                  for(int j = 1; j < image.height()-1; j++){
                      // Extract 3x3 window...
                      CustomMatrix mat(local_window);
                      allWindows.push_back(mat);
                      // Pattern matching
                      if(!mat.isEmpty()){
                          for(const auto& pattern : detectorPatterns){
                              if(matchPattern(mat, pattern, 0.66f)){
                                  candidatePositions.push_back(QPoint(i, j));
                                  break;
                              }
                          }
                      }
                  }
              }
              dumpWindowsToFile("window_dump.txt");
              analyzeWindows();
              isDetectionDone = true;
              update(); // Trigger visualization
          }
  3. Visualization
       Purple Rectangle Marking :
         void DrawingCanvas::paintEvent(QPaintEvent *event){
              // ... draw user points and lines ...
              if(isDetectionDone && !candidatePositions.empty()){
                  QPen purplePen(Qt::magenta, 1);
                  painter.setPen(purplePen);
                  painter.setBrush(Qt::NoBrush);
                  for(const QPoint& candidate : candidatePositions){
                      painter.drawRect(candidate.x()-2, candidate.y()-2, 4, 4);
                  }
              }
          }
  4. Output Files
     1. window_dump.txt berisi data mentah yang digunakan untuk verifikasi manual kualitas jendela dan fitur yang ditangkap.
     2. window_analysis.txt berisi ringkasan statistik dan hasil pemrosesan otomatis, yang digunakan untuk analisis kuantitatif efektivitas ukuran jendela dan pola.


