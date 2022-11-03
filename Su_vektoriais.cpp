#include "mylib.hpp"
#include "Studentas.hpp"
#include "funkcijos.hpp"

int main(){
  struct duom asmuo1, temp;
  vector<duom>masyvas;
  int paz, pazymiuKiekis, m, failoDydis;
  string arNuoFailo, failoPavadinimas, arSugeneruoti, kriterijus;
  std::chrono::duration<double>diff;
  std::chrono::duration<double>suma;

  while (true){
    cout << "Ar galutini bala skaiciuoti pagal vidurki ar mediana? V/M ";
    cin >> kriterijus;
    cout << "Ar duomenis skaitysite nuo failo? T/N ";
    cin >> arNuoFailo;
    if (arNuoFailo == "T" || arNuoFailo == "N"){
      if (arNuoFailo == "T"){  
        while (true){
          cout << "Ar norite sugeneruoti faila? T/N ";
          cin >> arSugeneruoti;
          if (arSugeneruoti == "T" || arSugeneruoti == "N") break;
        }
        break;
      }
      else break;
    }
    else cout << "Neteisinga ivestis. Pakartokite ivesti" << endl;
  }
  
  if (arSugeneruoti == "T"){
    cout << "Kokio dydzio bus failas?: ";
    cin >> failoDydis;
    generuoti(failoDydis, random());
    failoPavadinimas = "in" + std::to_string(failoDydis) + ".txt";
  }

  if (arNuoFailo == "T"){
    if (arSugeneruoti == "N"){
    cout << "Iveskite failo pavadinima: ";
    cin >> failoPavadinimas;
    }
    auto start = std::chrono::high_resolution_clock::now();
    string line;
    std::ifstream fd;
    fd.open(failoPavadinimas, std::ios::in);
      std::getline(fd, line);
      pazymiuKiekis = 1;
      int ilgis = line.size();
      for (int j = 1; j <= ilgis; j++){
        if (line[j-1] == ' ' && line[j] != ' ') pazymiuKiekis++;
      }
    
      while(!fd.eof()){
        fd >> asmuo1.var >> asmuo1.pav;
        for (int i =0; i<pazymiuKiekis-3; i++){
          fd >> paz;
          asmuo1.paz.push_back(paz);
        }
        fd >> asmuo1.egz;
        masyvas.push_back(asmuo1);
        asmuo1 = temp;
      }

      fd.close();
      auto end = std::chrono::high_resolution_clock::now();
      diff=end-start;
      cout << "Nuskaite per: " << diff.count() << endl;
      suma += diff;
    
    for (int i = 0; i < masyvas.size(); i++){
      masyvas[i].galutinis[0] = galutinis(masyvas[i], "Vid");
      masyvas[i].galutinis[1] = galutinis(masyvas[i], "Med");
    }
  }
  else {
    char b = '1';
    while (b != 'T'){
      masyvas.push_back(ivedimas(m));
      masyvas[masyvas.size()-1].galutinis[0] = galutinis(masyvas[masyvas.size()-1], "Vid");
      masyvas[masyvas.size()-1].galutinis[1] = galutinis(masyvas[masyvas.size()-1], "Med");
      cout << "Ar norite baigti ivedima? T/N ";
      cin >> b;
    } 
  }
  
  auto start = std::chrono::high_resolution_clock::now();

  vector<duom> masyvas2;
  masyvas2 = skirstykStudentus(masyvas, kriterijus);

  std::sort(masyvas.begin(), masyvas.end(), [](duom a, duom b){
    if (a.galutinis[0] != b.galutinis[0])
	    return a.galutinis[0] > b.galutinis[0];	
    else
      return a.galutinis[1] > b.galutinis[1];
  });

  std::sort(masyvas2.begin(), masyvas2.end(), [](duom a, duom b){
    if (a.galutinis[0] != b.galutinis[0])
	    return a.galutinis[0] > b.galutinis[0];	
    else
      return a.galutinis[1] > b.galutinis[1];
  });

  auto end = std::chrono::high_resolution_clock::now();
  diff=end-start;
  cout << "Surusiavo per: " << diff.count() << endl;
  suma += diff;

  std::ofstream fr("out" + std::to_string(failoDydis) + "galvociai.txt");
  std::ofstream fr2("out" + std::to_string(failoDydis) + "vargsiukai.txt");
  fr << std::left << std::setw (15) << "Vardas" << std::setw (15) << "Pavarde"  << std::setw (20) << "Galutinis (Vid.)" << std::setw (15) << "Galutinis (Med.)"<< endl; 
  fr << std::setw(65) << std::setfill('-') << "" << std::setfill(' ') << endl;
  fr2 << std::left << std::setw (15) << "Vardas" << std::setw (15) << "Pavarde"  << std::setw (20) << "Galutinis (Vid.)" << std::setw (15) << "Galutinis (Med.)"<< endl; 
  fr2 << std::setw(65) << std::setfill('-') << "" << std::setfill(' ') << endl;
  for (int i=0;i<masyvas.size();i++){
      std::stringstream a;
      temp = masyvas[i];
      a << std::left << setw (15) << temp.var << std::setw(20) << temp.pav << std::setw(21) << std::setprecision(3) << temp.galutinis[0] << std::setw(5) << temp.galutinis[1] << endl;
      fr << a.str();
      fr.clear();
  }
  for (int i=0;i<masyvas2.size();i++){
      std::stringstream a;
      temp = masyvas2[i];
      a << std::left << setw (15) << temp.var << std::setw(20) << temp.pav << std::setw(21) << std::setprecision(3) << temp.galutinis[0] << std::setw(5) << temp.galutinis[1] << endl;
      fr2 << a.str();
      fr2.clear();
  }
  cout << "Is viso: " << suma.count() << endl;
}

