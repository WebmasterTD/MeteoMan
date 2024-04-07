var tempGraph = echarts.init(document.getElementById('temp_graph'));
var humidGraph = echarts.init(document.getElementById('humid_graph'));
var rainGraph = echarts.init(document.getElementById('rain_graph'));

const data = {
    start: "2024-02-28 08:00:00"
};

async function getData() {
    const response = await fetch("api/data/getrange", { method: "QUERY", body: JSON.stringify(data) });
    return response.json();
}

getData().then((json_data) => {
    console.log(json_data);
    tempGraph.setOption({
        tooltip: {
            trigger: 'axis',
        },
        dataset: {
            source: json_data,
            dimensions: ['timestamp', 'temperature', 'humidity', 'rainfall'],
        },
        xAxis: {
            type: 'time',
            axisTick: {
                alignWithLabel: true,
            },
        },
        yAxis: {
            type: 'value',
            name: 'Temperature',
            position: 'left',
            axisLabel: {
                formatter: '{value} °C',
            },
        },
        series: {
            name: 'temperature',
            type: 'line',
            smooth: true,
            itemStyle: {
                color: '#db4444',
            },
            encode: {
                x: 'timestamp',
                y: 'temperature',
            },
        },
    });

    humidGraph.setOption({
        tooltip: {
            trigger: 'axis',
        },
        dataset: {
            source: json_data,
            dimensions: ['timestamp', 'temperature', 'humidity', 'rainfall'],
        },
        xAxis: {
            type: 'time',
            axisTick: {
                alignWithLabel: true,
            },
        },
        yAxis: {
            type: 'value',
            name: 'Humidity',
            position: 'left',
            axisLabel: {
                formatter: '{value} %',
            },
        },
        series: {
            name: 'humidity',
            type: 'line',
            smooth: true,
            itemStyle: {
                color: '#88bf49'
            },
            encode: {
                x: 'timestamp',
                y: 'humidity'
            }
        },
    });
    rainGraph.setOption({
        tooltip: {
            trigger: 'axis',
        },
        dataset: {
            source: json_data,
            dimensions: ['timestamp', 'temperature', 'humidity', 'rainfall'],
        },
        xAxis: {
            type: 'time',
            axisTick: {
                alignWithLabel: true,
            },
        },
        yAxis: {
            type: 'value',
            name: 'Percipitation',
            position: 'left',
            axisLabel: {
                formatter: '{value} mm',
            },
        },
        series: {
            name: 'rainfall',
            type: 'bar',
            itemStyle: {
                color: '#4d76b8'
            },
            encode: {
                x: 'timestamp',
                y: 'rainfall'
            }
        },
    });
});
    window.addEventListener('resize', function () {
        tempGraph.resize();
    });



    window.addEventListener('resize', function () {
        humidGraph.resize();
    });


    window.addEventListener('resize', function () {
        rainGraph.resize();
    });
