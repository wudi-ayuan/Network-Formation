library(igraph)
set.seed(2016)
g <-
  read.graph(
    "/Users/davidlai/Documents/UCLA EE/Job/C++/Network_Fromation/Network_Fromation/graph.txt",
    format = "edgelist",
    directed = 'FALSE'
  )
graph_data<-read.table("/Users/davidlai/Documents/UCLA EE/Job/C++/Network_Fromation/Network_Fromation/graph_data.txt",header=T,sep="\t")
j=1
for (i in 1: length(E(g))){
	test=E(g)[1:i]
	g1=subgraph.edges(g,test)
	j=(i+1)*i/2
	#dev.new()
	layout(matrix(c(1,1,1,2,3,4),2,3,byrow=TRUE))
	#layout.show(2) 	#par(mfrow=c(2,1))
	plot(g1)
	p=j-i+1

	barplot(as.matrix(graph_data[p:j,1]),main="Private",ylab="likelihood",xlab=paste("max is ", which(graph_data[p:j,1]==max(graph_data[p:j,1]))),beside=TRUE)
	barplot(as.matrix(graph_data[p:j,2]),main="Public",ylab="likelihood",xlab=paste("max is ", which(graph_data[p:j,2]==max(graph_data[p:j,2]))),beside=TRUE)
	barplot(as.matrix(graph_data[p:j,3]),main="Utility",ylab="Score",xlab=paste("max is ", which(graph_data[p:j,3]==max(graph_data[p:j,3]))),beside=TRUE)
	
#	dev.new()
#	plot(degree_distribution(g1))

	cat ("Press [enter] to continue")
	line <- readline()
#	dev.off()
#	dev.off()
}

dev.new()
