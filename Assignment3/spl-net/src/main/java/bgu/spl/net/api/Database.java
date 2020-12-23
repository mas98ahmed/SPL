package bgu.spl.net.api;


import bgu.spl.net.api.Users.*;

import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Passive object representing the Database where all courses and users are stored.
 * <p>
 * This class must be implemented safely as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add private fields and methods to this class as you see fit.
 */
public class Database {
	private static Database singleton = null;
	private final ConcurrentHashMap<Integer, Course> courses = new ConcurrentHashMap<>();
	private final ConcurrentHashMap<String, User> users = new ConcurrentHashMap<>();

	//to prevent user from creating new Database
	private Database() {
	}

	/**
	 * Retrieves the single instance of this class.
	 */
	public static Database getInstance() {
		if(singleton == null)
			singleton = new Database();
		return singleton;
	}
	
	/**
	 * loades the courses from the file path specified 
	 * into the Database, returns true if successful.
	 */
	public boolean initialize(String coursesFilePath) {
		try {
			File myObj = new File(coursesFilePath);
			Scanner myReader = new Scanner(myObj);
			while (myReader.hasNextLine()) {
				String data = myReader.nextLine();
				String[] line = data.split("\\|");
				int courseNum = Integer.parseInt(line[0]);
				String courseName = line[1];
				String[] kdamcourses = line[2].substring(1).split(",");
				List<Integer> kdamnums = new ArrayList<>();
				for(String s : kdamcourses){
					kdamnums.add(Integer.valueOf(s));
				}
				int maxStudentNum = Integer.parseInt(line[3]);
				courses.putIfAbsent(courseNum,new Course(courseNum,courseName,kdamnums,maxStudentNum));
				System.out.println(data);
			}
			myReader.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	public User getUser(String username){
		return users.get(username);
	}
	public synchronized boolean Register(User user) {
		if(!users.containsKey(user.getUsername())) {
			users.putIfAbsent(user.getUsername(), user);
			return true;
		}
		return false;
	}


	public boolean Login(String username, String password) {
		if(users.containsKey(username)){
			if(users.get(username).getPassword() == password){
				return true;
			}
		}
		return false;
	}

	public boolean CourseRegister(User activeUser, int courseNum) {
		Course course = courses.get(courseNum);
		boolean output = course.RegisterStudent(activeUser);
		if(output)
			activeUser.RegisterCourse(course);
		return output;
	}

	public String getKdamCourses(int courseNum) {
		Course course = courses.get(courseNum);
		return course.getKdamCoursesList().toString();
	}

	public boolean Unregister(User activeuser, int courseNum) {
		if(activeuser.getCourses().contains(courseNum)) {
			activeuser.getCourses().remove(courseNum);
			return true;
		}
		return false;
	}

	public String CourseStat(int courseNum) {
		Course course = courses.get(courseNum);
		return course.toString();
	}

	public String StudentStat(String username) {
		User student = users.get(username);
		return student.toString();
	}
}
