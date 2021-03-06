/*
Copyright (c) 2014, Hui Liang
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to 
endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Reference
[1] Hui Liang, Junsong Yuan and Daniel Thalmann, Parsing the Hand in Depth Images, in IEEE Trans. Multimedia, Aug. 2014.
[2] Hui Liang and Junsong Yuan, Hand Parsing and Gesture Recognition with a Commodity Depth Camera, 
in Computer Vision and Machine Learning with RGB-D Sensors, Springer, 2014.
*/

#pragma once
#include <stdio.h>
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv\cv.hpp>
#include "RandomTest.h"
using namespace std;

class Result
{
public:
	std::vector<double>	Conf;
	int						Pred;
};

class RDTNode 
{
public:
	RDTNode(void);
	RDTNode(int nDepth, int nClassNum, int nFeatureDim);
	~RDTNode();
	Result	eval(cv::Point p);			

public:
	void	setLabel(int nNodeLabel) { m_nNodeLabel = nNodeLabel; }
	bool	isLeaf(void) { return m_bLeaf; }
	bool	isRoot(void) {return m_bRoot; }
	void	readNode(FILE *pFile, std::vector<RDTNode*> &vecNodes);

private:
	bool			m_bLeaf;									// whether the node is a leaf
	bool			m_bRoot;									// whether the node is a root
	int				m_nDepth;									// the tree level of the current node
	int				m_nLabel;									// the hand part label
	int				m_nNodeLabel;							// the unique label to identify a tree node
	double			m_fCounter;
	std::vector<double>	m_vecLabelStats;
	HyperPlaneTest		m_tOpt;

private:	// these parameters are used across the whole random forest
	int				m_nClassNum;							
	int				m_nFeatureDim;					

private:	// the left and right children nodes
	RDTNode*	m_pLeftChildNode;
	RDTNode*	m_pRightChildNode;
};