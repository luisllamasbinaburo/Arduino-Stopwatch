/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "StopwatchLib.h"

Stopwatch::Stopwatch()
{
	Reset();
}

void Stopwatch::Reset()
{
	_lastMicros = micros();
}

void Stopwatch::Update()
{
	_rawElapsed = micros() - _lastMicros;
	_elapsed= (_rawElapsed >= _tuning) ? _rawElapsed - _tuning : 0;
}

unsigned long Stopwatch::GetElapsed() const
{
	return _elapsed;
}

float Stopwatch::GetFrequency() const
{
	return  1000000.0f / _elapsed;
}

void Stopwatch::Measure(StopwatchAction action)
{
	this->Reset();
	action();
	Update();
}

void Stopwatch::SetTune(unsigned long tune)
{
	_tuning = tune;
}

void Stopwatch::AutoTune()
{
	unsigned long t1, tdelta, lower = ~0UL;
	//test the millis timings (autotune)
	for(int i=0;i<100;i++){
		t1 = micros();
		micros();
		tdelta = micros() - t1;
		if( tdelta < lower ){
			lower = tdelta;
		}
	}
	SetTune(lower);
}
