using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml;

namespace LSForm
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            Grid grid = new Grid();
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(24.0) });
            grid.ColumnDefinitions.Add(new ColumnDefinition());
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(24.0) });
            grid.Margin = new Thickness(0.0, 0.0, 0.0, 8.0);
            TextBox boxR = new TextBox();
            boxR.Text = "R";
            Grid.SetColumn(boxR, 0);
            TextBox boxE = new TextBox();
            boxE.Margin = new Thickness(8.0, 0.0, 8.0, 0.0);
            boxE.Text = $"Rule #{StackRules.Children.Count}";
            Grid.SetColumn(boxE, 1);
            Button button = new Button();
            button.Content = "-";
            Grid.SetColumn(button, 2);
            grid.Children.Add(boxR);
            grid.Children.Add(boxE);
            grid.Children.Add(button);
            StackRules.Children.Insert(StackRules.Children.Count - 1, grid);
        }
    }
}
