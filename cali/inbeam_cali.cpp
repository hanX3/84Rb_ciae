
#define DEBUG 1

void inbeam_cali(int run_num, int channel_num)
{
	char finname[1024];
	sprintf(finname, "./inbeam_channel_energy/%04d/ch%02d", run_num, channel_num);
	cout << "cali file " << finname << endl;

	std::ifstream file_in;
	file_in.open(finname, std::ifstream::in);
	if(!file_in){
		cout<<"can not open "<<finname<<endl;
		return;
	}

	double ach; 
	double aen;
	map<double,double> map_channel_energy;

	while(1){
		ach = 0;
		aen = 0;

		file_in >> ach >> aen;
		if(file_in.eof()) break;
		map_channel_energy.insert({ach, aen});
	}

	TGraph *gr = new TGraph();
	auto it = map_channel_energy.cbegin();
	int graph_point_num = 0;
	while(it!=map_channel_energy.cend()){
		gr->SetPoint(graph_point_num, it->first, it->second);
		++graph_point_num;
		++it;
	}
	
	TFitResultPtr res = gr->Fit("pol2", "SQ");

#if DEBUG
		//	cout each points deviation
		double p0 = res->Parameter(0);
		double p1 = res->Parameter(1);
		double p2 = res->Parameter(2);
		cout << "deviation ..." << endl;
		auto it_debug = map_channel_energy.cbegin();
		while(it_debug != map_channel_energy.cend()){
			cout << it_debug->second << "  " << p0+p1*it_debug->first+p2*it_debug->first*it_debug->first-it_debug->second << endl;
			++it_debug;
		}
		cout << "chi2 = " << res->Chi2() << endl;
		cout << endl << endl;
#endif

	// write
	std::ofstream file_out;
	char file_out_name[2014];
	sprintf(file_out_name, "./inbeam_cali_par/%04d.txt", run_num);

	file_out.open(file_out_name, std::ofstream::out | std::ofstream::app);
	file_out << channel_num << "  " << res->Chi2() << "  " << res->Parameter(0) << "  " << res->Parameter(1) << "  " << res->Parameter(2) << endl;

	file_in.close();
	file_out.close();
}
